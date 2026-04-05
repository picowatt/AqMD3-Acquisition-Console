#ifndef STREAM_READER_H
#define STREAM_READER_H

#include <libaqmd3/streamingcontext.h>
#include <memory>
#include <future>

class StreamReader
{
private:
    std::shared_ptr<StreamingContext> digitizer;
    std::shared_ptr<AcquisitionBufferPool> buffer_pool;
    uint64_t timeout;

    public :
        StreamReader(std::shared_ptr<StreamingContext> digitizer, int64_t, std::shared_ptr<AcquisitionBufferPool> buffer_pool,
                     uint64_t timeout)
            : digitizer(digitizer)
            , buffer_pool(buffer_pool)
            , timeout(timeout)
        {
        }
    
        AcquiredData read(uint64_t tof_scans_to_acquire) const;

     virtual ~StreamReader() = default;
};

#endif