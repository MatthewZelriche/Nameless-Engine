cmake_minimum_required(VERSION 3.13.0)

project(NamelessEngine)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# For some reason, while doing a clean rebuild everything broke, I had to add this.
# Otherwise cmake would try to make a file named bin instead of a dir named bin
# When setting runtime and library directory.
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin")

configure_file("${CMAKE_SOURCE_DIR}/LICENSE.md" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin" COPYONLY)


set(VENDOR_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/Vendor/glfw/include"
                        "${CMAKE_SOURCE_DIR}/Vendor/Nameless-Logger/include"
                        "${CMAKE_SOURCE_DIR}/Vendor/glm/"
                        "${CMAKE_SOURCE_DIR}/Vendor/robin-hood-hashing/include/"
                        "${CMAKE_SOURCE_DIR}/Vendor/LeksysINI/"
                        "${CMAKE_SOURCE_DIR}/Vendor/glad/include/"
                        "${CMAKE_SOURCE_DIR}/Vendor/tinyxml2/"
                        "${CMAKE_SOURCE_DIR}/Vendor/NETCore/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/NamelessLib/")
add_subdirectory("${CMAKE_SOURCE_DIR}/Apps/Editor")

