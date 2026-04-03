project (AqMD3_console)

find_package(spdlog CONFIG REQUIRED)

include_directories("C:/Program Files/IVI Foundation/IVI/Include")
link_directories("C:/Program Files/IVI Foundation/IVI/Lib_x64/msc")

include_directories("C:/Program Files/IVI Foundation/VISA/Win64/Include")
link_directories("C:/Program Files/IVI Foundation/VISA/Win64L/lib_x64/msc")

add_executable (AqMD3_console 
	src/aqmd3_cli.cpp
	)

target_link_libraries(AqMD3_console PRIVATE AqLio)

target_link_libraries (AqMD3_console PUBLIC i::uimf)
target_link_libraries (AqMD3_console PUBLIC i::digi)

target_link_libraries(AqMD3_console PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
