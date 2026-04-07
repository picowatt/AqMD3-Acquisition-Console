#ifndef ZMQ_ACQUIRED_DATA_SUBSCRIBER_H
#define ZMQ_ACQUIRED_DATA_SUBSCRIBER_H

#include "server/server.h"
#include <pubsub/subscriber.h>
#include <libaqmd3/acquireddata.h>
#include <UIMFWriter/uimfframe.h>
#include <zmq.hpp>

#include <string>
#include <iostream>

class ZmqAcquiredDataSubscriber : public Subscriber<std::shared_ptr<UimfFrame>> {
private:
	std::shared_ptr<Server::Publisher> publisher;
	std::string subject;
	std::vector<int32_t> data_vector;
	uint64_t processed;

public:
	ZmqAcquiredDataSubscriber(std::shared_ptr<Server::Publisher> publisher, uint32_t sample_count)
		: Subscriber()
		, data_vector(sample_count)
		, publisher(publisher)
		, subject("data")
		, processed(0)
	{}

private:
	void on_notify(std::shared_ptr<UimfFrame>& item) override;
	void on_completed() override;
};

#endif // ZMQ_ACQUIRED_DATA_SUBSCRIBER_H
