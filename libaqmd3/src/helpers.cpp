#include "../include/libaqmd3/helpers.h"


namespace aqmd3
{
	void check_and_throw_on_error(std::pair<std::string, enum Digitizer::ErrorType> err)
	{
		if (err.second == Digitizer::Error)
		{
			throw std::runtime_error(std::format("Error during call to digitizer. {}", err.first));
		}
	}
}