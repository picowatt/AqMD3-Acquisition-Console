#ifndef ACQUIRE_PUBLISHER_H
#define ACQUIRE_PUBLISHER_H

#include "pubsub/publisher.h"
#include "uimf/uimfacquisitionrecord.h"

class AcquisitionPublisher : public Publisher<UimfAcquisitionRecord>
{
public:
    AcquisitionPublisher() {}

};

#endif