project (core)

find_package(spdlog CONFIG REQUIRED)

add_library (core
	src/acquisitioncontroller.cpp
	src/processsubject.cpp
	src/uimfframewritersubscriber.cpp
	src/uimf/uimfacquisitionrecord.cpp
	src/massspec/toftiminginformation.cpp
	src/acquisition/streamreader.cpp
	include/acquisitionpublisher.h
	include/processsubject.h
	include/acquisitioncontroller.h
	include/uimfframewritersubscriber.h
	include/uimf/uimfacquisitionrecord.h
	include/pubsub/publisher.h
	include/pubsub/subscriber.h
	include/acquisition/acquisitioncontrol.h
	include/acquisition/streamreader.h
	include/diagnostic/datageneratorcontext.h
	include/mass_spec/toftiminginformation.h
	include/util/timehelpers.h
	)

add_library(i::core ALIAS core)


target_link_libraries (core PUBLIC i::uimf)
target_link_libraries (core PUBLIC i::digi)

target_link_libraries(core PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

target_include_directories ( core
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)
