#ifndef ACQUIRE_PUBLISHER_H
#define ACQUIRE_PUBLISHER_H


#include "acquisition/acquisitioncontrol.h"
#include "acquisition/streamreader.h"
#include "server/server.h"
#include <libaqmd3/streamingcontext.h>
#include <vector>
#include <thread>
#include <atomic>
#include <future>
#include <functional>


class AcquisitionController : public AcquisitionControl
{
private:
	std::unique_ptr<std::thread> worker_handle;//<
	std::atomic_bool should_stop;//<
	std::promise<State> stop_signal;//<

	StreamReader stream_reader;

	uint64_t tof_scans_to_acquire;
	//std::shared_ptr<Server::Publisher> publisher;
	//std::string subject;

public:
	AcquisitionController(StreamReader stream_reader, uint64_t tof_scans_to_acquire
	//	std::shared_ptr<Server::Publisher> publisher
	)
		: worker_handle()
		, should_stop(false)
		, stream_reader(stream_reader)
		, tof_scans_to_acquire(tof_scans_to_acquire)
	//	, publisher(publisher)
	//	, subject("status")
	{}
	virtual ~AcquisitionController() = default;

	void start(UimfFrameParameters parameters, std::function<void(void)> on_scans_acquired = nullptr, std::function<void(void)> on_acquisition_completed = nullptr);
	void stop(bool terminate_acquisition_chain) override;
};

#endif // !ACQUIRE_PUBLISHER_H
