cmake_minimum_required(VERSION 3.13.0)

project(TemplateProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")

set(SOURCES     "main.cpp")

add_executable(TemplateProject ${SOURCES})
