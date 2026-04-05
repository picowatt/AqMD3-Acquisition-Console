project (core)


find_path(PICOSHA2_INCLUDE_DIRS "picosha2.h")

find_package(cppzmq CONFIG REQUIRED) 
find_package(protobuf CONFIG REQUIRED)
find_package(Snappy CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_library (core
	src/message.pb.cpp
	src/acquirepublisher.cpp
	src/processsubject.cpp
	src/zmqacquireddatasubscriber.cpp
	src/uimfframewritersubscriber.cpp
	src/uimfacquisitionrecord.cpp
	src/server/server.cpp
	src/massspec/toftiminginformation.cpp
	include/message.pb.h
	include/acquisitionpublisher.h
	include/processsubject.h
	include/zmqacquireddatasubscriber.h
	include/acquisitioncontroller.h
	include/uimfframewritersubscriber.h
	include/uimf/uimfacquisitionrecord.h
	include/pubsub/publisher.h
	include/pubsub/subscriber.h
	include/server/server.h
	include/acquisition/acquisitioncontrol.h
	include/diagnostic/datageneratorcontext.h
	include/mass_spec/toftiminginformation.h
	include/util/timehelpers.h
	include/util/uimfhelpers.h
	)

add_library(i::core ALIAS core)

target_include_directories(core PRIVATE ${PICOSHA2_INCLUDE_DIRS})

target_link_libraries(core PRIVATE cppzmq cppzmq-static)
target_link_libraries(core PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(core PRIVATE Snappy::snappy)

target_link_libraries (core PUBLIC i::uimf)
target_link_libraries (core PUBLIC i::digi)

target_link_libraries(core PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

target_include_directories ( core
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)
