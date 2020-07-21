cmake_minimum_required(VERSION 3.13.0)

project(NamelessEngine)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# For some reason, while doing a clean rebuild everything broke, I had to add this.
# Otherwise cmake would try to make a file named bin instead of a dir named bin
# When setting runtime and library directory.
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/NamelessLib/")
add_subdirectory("${CMAKE_SOURCE_DIR}/Apps/Example-App")

