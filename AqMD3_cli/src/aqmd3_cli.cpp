#include <iostream>
#include <string>
#include <cxxopts.hpp>


int main(int argc, char *argv[])
{
    try
    {
        cxxopts::Options options("AqMD3_cli", "A CLI for controlling the digitizers");

        // Define options
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



    }
    catch (const cxxopts::exceptions::exception &e)
    {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}