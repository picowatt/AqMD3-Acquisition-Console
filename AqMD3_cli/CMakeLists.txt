project (AqMD3_cli)

find_package(cxxopts CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
set(VISA_LIB_DIR "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc")

find_library(VISA_LIBRARY
    NAMES visa visa32 visa64
    PATHS "${VISA_LIB_DIR}"
    NO_DEFAULT_PATH
)

add_executable (AqMD3_cli
	src/aqmd3_cli.cpp
	src/visa/visainterface.cpp
	include/visa/visainterface.h
	)

target_link_libraries (AqMD3_cli
	PRIVATE
		i::core
		TBB::tbb
		cxxopts::cxxopts
)

target_include_directories(AqMD3_cli PRIVATE ${VISA_INCLUDE_DIR})
target_link_libraries(AqMD3_cli PRIVATE ${VISA_LIBRARY})
