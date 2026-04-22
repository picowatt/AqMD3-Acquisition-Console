#ifndef DEVICE_CONSTANTS_H
#define DEVICE_CONSTANTS_H

#include "digitizerconfigurabletype.h"
#include <unordered_map>
#include <variant>
#include <string>
#include <vector>


template <typename T>
struct DeviceConstants;

template <typename T>
std::unordered_map<DigitizerConfigurableType, std::variant<std::vector<std::string>, std::vector<double>>> get_device_constants_map()
{
    return DeviceConstants<T>::get_device_constants_map();
}

#endif