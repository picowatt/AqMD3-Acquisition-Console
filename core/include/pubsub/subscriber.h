#ifndef FRAME_SUBSCRIBER_H
#define FRAME_SUBSCRIBER_H

#include <deque>
#include <mutex>
#include <condition_variable>
#include <future>
#include <spdlog/spdlog.h>
#include <iostream>
#include <exception>
using std::cerr;

enum class SubscriberType : uint8_t
{
	ACQUIRE = (1 << 0),
	ACQUIRE_FRAME = (1 << 1),
	BOTH = (1 << 0)|(1 << 1),
};

constexpr enum SubscriberType operator|(const enum SubscriberType left, const enum SubscriberType right)
{
	return (enum SubscriberType)(uint8_t(left) | uint8_t(right));
}

constexpr enum SubscriberType operator&(const enum SubscriberType left, const enum SubscriberType right)
{
	return (enum SubscriberType)(uint8_t(left) & uint8_t(right));
}

template <typename T>
class Subscriber {
private:
	std::thread worker_handle;
	std::condition_variable sig;
	std::mutex sig_mutex;

	std::promise<void> has_completed;
	std::shared_future<void> stop_fut;
	
	bool is_running;
	
	std::deque<T> protected_queue;
	std::mutex protected_queue_mutex;

	bool drain_queue_on_stop;

protected:
	std::deque<T> items;

public:
	Subscriber(bool drain_queue_on_stop = true)
		: items()
		, worker_handle()
		, is_running(false)
		, drain_queue_on_stop(drain_queue_on_stop)
	{}

	virtual ~Subscriber()
	{
		if (worker_handle.joinable()) {
			worker_handle.join();
		}
	};

	std::shared_future<void> setup(std::shared_future<void> pub_stop)
	{
		this->stop_fut = pub_stop;

		if (!is_running)
		{
			worker_handle = std::thread([&]()
			{
				is_running = true;
				while (true)
				{
					if (stop_fut.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
					{
						if (!drain_queue_on_stop)
						{
							break;
						}

						{
							const std::lock_guard<std::mutex> lock(protected_queue_mutex);
							if (protected_queue.empty() && items.empty())
							{
								break;
							}
						}
					}

					{
						std::unique_lock<std::mutex> lock(sig_mutex);
						sig.wait_for(lock, std::chrono::milliseconds(10));
					}

					{
						const std::lock_guard<std::mutex> lock(protected_queue_mutex);
						for (int i = 0; i < protected_queue.size(); i++)
						{
							items.push_back(protected_queue.front());
							protected_queue.pop_front();
						}
					}

					while (!items.empty())
					{
						T item = items.front();
						items.pop_front();
						try
						{
							on_notify(item);
						}
						catch (const std::exception &ex)
						{
							continue;
						}
					}
				}
				try
				{
					on_completed();
				}
				catch (const std::exception &ex)
				{
					continue;
				}

				has_completed.set_value();
			});
		}
		return std::shared_future<void>(has_completed.get_future());
	}

	inline void update(T item)
	{
		const std::lock_guard<std::mutex> lock(protected_queue_mutex);
		protected_queue.push_back(item);
		sig.notify_one();
	}

private:
	virtual inline void on_notify(T& item) {};
	virtual inline void on_completed() {};
};

#endif // !FRAME_SUBSCRIBER_H
