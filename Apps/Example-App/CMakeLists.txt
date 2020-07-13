cmake_minimum_required(VERSION 3.13.0)

project(ExampleApp)

set(SOURCES     "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp")

add_executable(ExampleApp ${SOURCES})
target_link_libraries(ExampleApp NamelessLib)