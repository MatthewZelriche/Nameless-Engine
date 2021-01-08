cmake_minimum_required(VERSION 3.13.0)

project(CoreExecutable)

set(SOURCES     "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/include/extern.hpp")

add_executable(CoreExecutable ${SOURCES})

set_target_properties(CoreExecutable PROPERTIES 
                        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/CoreExecutable/$<0:>
                        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/CoreExecutable/$<0:>
                        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/CoreExecutable/$<0:>)

target_link_libraries(CoreExecutable NamelessLib)