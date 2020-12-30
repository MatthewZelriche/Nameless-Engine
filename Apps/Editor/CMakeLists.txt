cmake_minimum_required(VERSION 3.13.0)

project(NamelessEditor)

set(SOURCES     "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp")

configure_file("${CMAKE_SOURCE_DIR}/Apps/Editor/config/controls.ini" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin" COPYONLY)
configure_file("${CMAKE_SOURCE_DIR}/Apps/Editor/config/settings.ini" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin" COPYONLY)

add_executable(NamelessEditor ${SOURCES})

set_target_properties(NamelessEditor PROPERTIES 
                        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/$<0:>
                        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/$<0:>
                        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/$<0:>)

target_include_directories(NamelessEditor PUBLIC ${VENDOR_INCLUDE_DIRS})
set_property(TARGET NamelessEditor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")
target_link_libraries(NamelessEditor NamelessLib)