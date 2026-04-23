#include <libaqmd3/digitizers/sa220p.h>
#include <libaqmd3/devicevalues/deviceconstants.h>
#include <libaqmd3/devicevalues/digitizerconfigurabletype.h>
#include <iostream>
#include <string>
#include <cxxopts.hpp>
#include <string>
#include <vector>
#include <variant>
#include <unordered_map>


int main(int argc, char *argv[])
{
    try
    {
        cxxopts::Options options("AqMD3_cli", "A CLI for controlling the digitizers");

        options.add_options()
            ("h,help", "Print help")
            ("d,digitizer", "The digitizer", cxxopts::value<std::string>()->default_value("SA220P"));

        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            return 0;
        }

        std::string name = result["digitizer"].as<std::string>();

        auto digi_consts = aqmd3::get_device_constants_map<aqmd3::SA220P>();

        // https://en.cppreference.com/cpp/utility/variant/visit2
        for (const auto &[key, values] : digi_consts)
        {
            std::visit([](const auto& vector)
            {
                for (const auto& elem : vector)
                {
                    std::cout << elem << std::endl;
                }
            }, values);
        }
    }
    catch (const cxxopts::exceptions::exception &e)
    {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}