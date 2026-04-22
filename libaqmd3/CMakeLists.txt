project (libaqmd3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IVI_INCLUDE_DIR "C:/Program Files/IVI Foundation/IVI/Include")
set(VISA_INCLUDE_DIR "C:/Program Files/IVI Foundation/VISA/Win64/Include")

set(IVI_LIB_DIR "C:/Program Files/IVI Foundation/IVI/Lib_x64/msc")
set(VISA_LIB_DIR "C:/Program Files/IVI Foundation/VISA/Win64/lib_x64/msc")

find_library(AQMD3_LIBRARY
    NAMES AqMD3
    PATHS "${IVI_LIB_DIR}"
    NO_DEFAULT_PATH
)

add_library (libaqmd3
	src/digitizer.cpp
	src/acquisitionbuffer.cpp
	src/streamingcontext.cpp
	src/acquireddata.cpp
	src/cstzs1context.cpp
	src/cstcontext.cpp
	src/digitizers/sa220.cpp
	src/acquisitionbufferpool.cpp
	include/libaqmd3/digitizer.h
	include/libaqmd3/acquisitionbuffer.h
	include/libaqmd3/streamingcontext.h
	include/libaqmd3/cstzs1context.h
	include/libaqmd3/cstcontext.h
	include/libaqmd3/acquireddata.h
	include/libaqmd3/digitizers/sa220.h
	include/libaqmd3/acquisitionbufferpool.h
 	include/libaqmd3/helpers.h
	include/libaqmd3/devicevalues/deviceconstants.h
	include/libaqmd3/devicevalues/digitizerconfigurabletype.h
	src/helpers.cpp
	)

add_library(i::digi ALIAS libaqmd3)

target_include_directories(libaqmd3
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${IVI_INCLUDE_DIR}
        ${VISA_INCLUDE_DIR}
)

target_link_libraries(libaqmd3
    PRIVATE
        ${AQMD3_LIBRARY}
    PUBLIC
        i::uimf
)