cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set (VCPKG_FEATURE_FLAGS "versions")
project (AqMD3_console VERSION 1.1.0)

# Include sub-projects.
add_subdirectory ("UIMFWriter")
add_subdirectory ("libaqmd3")
add_subdirectory ("core")
add_subdirectory ("AqMD3_console")
add_subdirectory ("AqMD3_cli")

target_compile_options(AqMD3_console PRIVATE "$<$<CONFIG:Release>:/Zi>")
target_compile_options(AqMD3_console PRIVATE "$<$<CONFIG:Release>:/EHa>")
target_link_options(AqMD3_console PRIVATE "$<$<CONFIG:Release>:/DEBUG>")
target_link_options(AqMD3_console PRIVATE "$<$<CONFIG:Release>:/OPT:REF>")
target_link_options(AqMD3_console PRIVATE "$<$<CONFIG:Release>:/OPT:ICF>")

# https://stackoverflow.com/a/63924044
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

configure_file(templates/app.h.in include/app.h)
target_include_directories(AqMD3_console PUBLIC "${PROJECT_BINARY_DIR}")