cmake_minimum_required(VERSION 3.13.0)

project(ExampleApp)

set(SOURCES     "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_executable(ExampleApp ${SOURCES})
target_link_libraries(ExampleApp NamelessLib)