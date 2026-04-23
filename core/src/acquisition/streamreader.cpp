#include "../../include/acquisition/streamreader.h"

aqmd3::AcquiredData StreamReader::read(uint64_t tof_scans_to_acquire) const
{
    return this->digitizer->acquire(tof_scans_to_acquire, std::chrono::milliseconds(this->timeout));
}