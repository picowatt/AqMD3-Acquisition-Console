project (AqMD3_console)

find_package(spdlog CONFIG REQUIRED)

set(VISA_INCLUDE_DIR "C:/Program Files/IVI Foundation/VISA/Win64/Include")
set(VISA_LIB_DIR "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc")

find_library(VISA_LIBRARY
    NAMES visa visa32 visa64
    PATHS "${VISA_LIB_DIR}"
    NO_DEFAULT_PATH
)

add_executable (AqMD3_console 
	src/aqmd3_console.cpp
	include/definitions.h
	include/config/config.h   
	)

target_include_directories(AqMD3_console PUBLIC ${VISA_INCLUDE_DIR})

target_link_libraries(AqMD3_console PRIVATE ${VISA_LIBRARY})

target_link_libraries (AqMD3_console PUBLIC i::core)
target_link_libraries(AqMD3_console PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

add_custom_command(TARGET AqMD3_console PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/config.txt $<TARGET_FILE_DIR:AqMD3_console>
)
add_custom_command(TARGET AqMD3_console POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/include/app.h $<TARGET_FILE_DIR:AqMD3_console>
)
