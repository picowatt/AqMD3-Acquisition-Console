#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <span>


struct Publisher
{
public:
    virtual ~Publisher() = default;
    virtual void publish(std::span<std::byte> &data) = 0;
};

#endif