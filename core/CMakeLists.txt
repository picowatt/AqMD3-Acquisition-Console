project (core)

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
	include/acquirepublisher.h
	include/acquisitioncontrol.h
	include/processsubject.h
	include/zmqacquireddatasubscriber.h
	include/uimfframewritersubscriber.h
	include/definitions.h
	include/uimfacquisitionrecord.h
	include/pubsub/publisher.h
	include/pubsub/subscriber.h
	include/server/server.h
	include/diagnostic/datageneratorcontext.h
	include/massspec/toftiminginformation.h
	include/util/timehelpers.h
	include/util/uimfhelpers.h
	)

target_include_directories ( core
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)
