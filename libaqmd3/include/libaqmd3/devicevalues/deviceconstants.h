#ifndef DEVICE_CONSTANTS_H
#define DEVICE_CONSTANTS_H

#include "digitizerconfigurabletype.h"
#include <unordered_map>
#include <variant>
#include <string>
#include <vector>

namespace aqmd3 
{
    using DeviceConstantsTypeMap = std::variant<std::vector<std::string>, std::vector<double>>;
    using DeviceConstantsMap = std::unordered_map<DigitizerConfigurableType, DeviceConstantsTypeMap>;

    template <typename T>
    struct DeviceConstants;

    template <typename T>
    DeviceConstantsMap get_device_constants_map()
    {
        return DeviceConstants<T>::get_device_constants_map();
    }
}

#endif