cmake_minimum_required(VERSION 3.13.0)

project(NamelessEditor)

set(SOURCES     "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.hpp"
                "${CMAKE_CURRENT_SOURCE_DIR}/src/Game.cpp")

# Move config files to bin directory. 
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config/controls.ini" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin" COPYONLY)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config/settings.ini" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin" COPYONLY)

add_executable(NamelessEditor ${SOURCES})
target_include_directories(NamelessEditor PUBLIC ${VENDOR_INCLUDE_DIRS})
set_property(TARGET NamelessEditor PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")
target_link_libraries(NamelessEditor NamelessLib)