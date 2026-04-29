#ifndef VISA_INTERFACE_H
#define VISA_INTERFACE_H

#include <string>
#include <vector>
#include <format>
#include <iostream>
#include <expected>

#include <visa.h>


namespace visa_interface 
{
    std::expected<std::vector<std::string>, std::string> get_device_list();
}

#endif
