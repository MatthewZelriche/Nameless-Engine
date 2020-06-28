cmake_minimum_required(VERSION 3.13.0)
include(GenerateExportHeader)
project(NamelessLib)

set(NLSLIB_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/")

set(NLSLIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Placeholder.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Placeholder.cpp")

add_library(NamelessLib SHARED ${NLSLIB_SOURCES})

set_target_properties(NamelessLib PROPERTIES CXX_VISIBILITY_PRESET hidden)
generate_export_header(NamelessLib BASE_NAME NLS_API EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Core/NLS_API_Export.h")
target_include_directories(NamelessLib PUBLIC ${NLSLIB_INCLUDE_DIRECTORIES})
