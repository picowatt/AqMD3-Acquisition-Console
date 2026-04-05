project (AqMD3_cli)

find_package(spdlog CONFIG REQUIRED)
find_package(cxxopts CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)

add_executable (AqMD3_cli
	src/aqmd3_cli.cpp
	)

target_link_libraries (AqMD3_cli
	PRIVATE
		i::core
		TBB::tbb
		cxxopts::cxxopts
		spdlog::spdlog
		spdlog::spdlog_header_only
)