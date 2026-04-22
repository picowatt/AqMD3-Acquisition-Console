project (AqMD3_console)

find_package(spdlog CONFIG REQUIRED)

set(VISA_INCLUDE_DIR "C:/Program Files/IVI Foundation/VISA/Win64/Include")
set(VISA_LIB_DIR "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc")

find_library(VISA_LIBRARY
    NAMES visa visa32 visa64
    PATHS "${VISA_LIB_DIR}"
    NO_DEFAULT_PATH
)

find_path(PICOSHA2_INCLUDE_DIRS "picosha2.h")
find_package(cppzmq CONFIG REQUIRED) 
find_package(protobuf CONFIG REQUIRED)
find_package(Snappy CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)

add_executable (AqMD3_console 
	src/aqmd3_console.cpp
	src/zmqacquireddatasubscriber.cpp
	src/message.pb.cpp
	src/server/server_zmq.cpp
	include/definitions.h
	include/config/config.h   
	include/zmqacquireddatasubscriber.h
	include/message.pb.h
	include/server/server_zmq.h
	include/server/publisher.h
	include/util/uimfhelpers.h
	)

target_include_directories(AqMD3_console PUBLIC ${VISA_INCLUDE_DIR})
target_include_directories(AqMD3_console PRIVATE ${PICOSHA2_INCLUDE_DIRS})

target_link_libraries(AqMD3_console PRIVATE ${VISA_LIBRARY})
target_link_libraries (AqMD3_console PUBLIC i::core)
target_link_libraries(AqMD3_console PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
target_link_libraries(AqMD3_console PRIVATE cppzmq cppzmq-static)
target_link_libraries(AqMD3_console PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(AqMD3_console PRIVATE Snappy::snappy)
target_link_libraries(AqMD3_console PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(AqMD3_console PRIVATE asio::asio)

add_custom_command(TARGET AqMD3_console PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/config.txt $<TARGET_FILE_DIR:AqMD3_console>
)
add_custom_command(TARGET AqMD3_console POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/include/app.h $<TARGET_FILE_DIR:AqMD3_console>
)
