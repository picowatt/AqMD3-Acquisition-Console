#ifndef PROCESS_SUBJECT_H
#define PROCESS_SUBJECT_H

#include "pubsub/subscriber.h"
#include "pubsub/publisher.h"
#include <libaqmd3/acquireddata.h>
#include <UIMFWriter/encodedresult.h>
#include <UIMFWriter/uimfframe.h>
#include "server/server.h"
#include <zmq.hpp>
#include "uimf/uimfacquisitionrecord.h"
#include <spdlog/spdlog.h>

#define NOMINMAX 
#undef min
#undef max
#include "message.pb.h"

using frame_ptr = std::shared_ptr<UimfFrame>;

class ProcessSubject : public Subscriber<UimfAcquisitionRecord>,
	public Publisher<frame_ptr> {
private:
	uint64_t total_triggers_processed;
	std::chrono::milliseconds total_duration;
	uint64_t tof_avg_samples;
	uint64_t notify_on_scans_count;

public:
	ProcessSubject(uint64_t tof_avg_samples)
		: total_triggers_processed(0)
		, tof_avg_samples(tof_avg_samples)
	{
	}

private:
	void on_notify(UimfAcquisitionRecord& item) override;

	void on_completed() override
	{
		spdlog::debug("Publisher<frame_ptr>::notify_completed_and_wait()");
		Publisher<frame_ptr>::notify_completed_and_wait();
	}
};

#endif // !PROCESS_SUBJECT_H
