cmake_minimum_required(VERSION 3.13.0)
include(GenerateExportHeader)
project(NamelessLib)

add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/glfw" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/Vendor/glfw")
add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/Nameless-Logger" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/Vendor/Nameless-Logger")
find_package(Doxygen)
find_package(Vulkan REQUIRED)


if(DOXYGEN_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/Doc/NamelessLib/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(DOXYGEN_DOCUMENTATION ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif(DOXYGEN_FOUND)


set(VENDOR_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Vendor/glfw/include"
                        "${CMAKE_SOURCE_DIR}/Vendor/Nameless-Logger/include"
                        "${CMAKE_SOURCE_DIR}/Vendor/glm/"
                        "${CMAKE_SOURCE_DIR}/Vendor/robin-hood-hashing/include/")
set(NLSLIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

set(NLSLIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Core/IGameTemplate.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/IGameTemplate.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/EventSystem/Event.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/EventSystem/EventCapable.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/EventSystem/EventCapable.cpp")

add_library(NamelessLib SHARED ${NLSLIB_SOURCES})

set_target_properties(NamelessLib PROPERTIES CXX_VISIBILITY_PRESET hidden)
generate_export_header(NamelessLib BASE_NAME NLS_API EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Core/NLS_API_Export.h")
target_include_directories(NamelessLib PUBLIC ${NLSLIB_INCLUDE_DIRS} ${VENDOR_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR})

target_link_libraries(NamelessLib glfw)
target_link_libraries(NamelessLib ${Vulkan_LIBRARIES})
target_link_libraries(NamelessLib NamelessLogger)
