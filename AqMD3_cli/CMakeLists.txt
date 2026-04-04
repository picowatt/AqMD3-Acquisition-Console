project (AqMD3_cli)

find_package(spdlog CONFIG REQUIRED)

add_executable (AqMD3_cli
	src/aqmd3_cli.cpp
	)

target_link_libraries (AqMD3_cli PUBLIC i::core)

target_link_libraries(AqMD3_cli PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
