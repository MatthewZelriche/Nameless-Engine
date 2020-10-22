cmake_minimum_required(VERSION 3.13.0)
include(GenerateExportHeader)
project(NamelessLib)

add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/glfw" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/Vendor/glfw")
add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/Nameless-Logger" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/Vendor/Nameless-Logger")
add_subdirectory("${CMAKE_SOURCE_DIR}/Vendor/tinyxml2" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/Vendor/tinyxml2")

if (MSVC)
	add_subdirectory("${CMAKE_SOURCE_DIR}/NamelessLib/CSharpLibs/" "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/Vendor/CSharpLibs")
endif()

find_package(Doxygen)
find_package(Vulkan REQUIRED)

configure_file(${CMAKE_SOURCE_DIR}/Vendor/NETCore/NLS.runtimeconfig.json ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin COPYONLY) 

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/Doc/NamelessLib/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(DOXYGEN_DOCUMENTATION ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif(DOXYGEN_FOUND)

set(NLSLIB_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

set(NLSLIB_SOURCES  "${CMAKE_SOURCE_DIR}/Vendor/glad/src/glad.c"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Core/IGameTemplate.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/IGameTemplate.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/EventSystem/Event.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/EventSystem/EventCapable.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/EventSystem/EventCapable.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/IO/KeyBindingSet.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/IO/ReadWriteFile.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/IO/ReadWriteFile.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/IO/KeyBindingSet.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Rendering/WindowManager.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Rendering/Window.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Rendering/GLContext.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Rendering/WindowManager.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Rendering/Window.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/IO/InputManager.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/IO/InputManager.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Rendering/GLContext.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/ECS/ComponentHandler.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/ECS/ComponentTypes.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/ECS/ECSManager.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Core/Utils.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Utils.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/SharpScripting/RuntimeHost.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/SharpScripting/RuntimeHost.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/SharpScripting/AssemblyManager.hpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/src/SharpScripting/AssemblyManager.cpp"
                    "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/SharpScripting/EngineDelegates.hpp")

add_library(NamelessLib SHARED ${NLSLIB_SOURCES})

if (MSVC)
    # To ensure functionality on Win10 with LeksysINI
	target_compile_options(NamelessLib PUBLIC "/Zc:__cplusplus")

    add_dependencies(NamelessLib NLSharp)
endif()

# net host for scripting.
find_library(nethost 
            NAMES 
                nethost.so libnethost.so nethost.lib
            HINTS 
		"C:/Program Files/dotnet/packs/Microsoft.NETCore.App.Host.win-x64/3.1.9/runtimes/win-x64/native"
                # DOTNET_ROOT MUST be set if net-core is installed on a non-standard location.
                "/usr/share/dotnet/packs/Microsoft.NETCore.App.Host.linux-x64/3.1.8/runtimes/linux-x64/native/"
                "$ENV{DOTNET_ROOT}/packs/Microsoft.NETCore.App.Host.linux-x64/3.1.8/runtimes/linux-x64/native/")

if (MSVC)
    find_file(nethost_dll
                NAMES
                    nethost.dll
                HINTS
                    "C:/Program Files/dotnet/packs/Microsoft.NETCore.App.Host.win-x64/3.1.9/runtimes/win-x64/native")
configure_file(${nethost_dll} ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/bin/ COPYONLY)
endif()

target_link_libraries(NamelessLib ${nethost})
set_target_properties(NamelessLib PROPERTIES CXX_VISIBILITY_PRESET hidden)
generate_export_header(NamelessLib BASE_NAME NLS_API EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/NLS-Engine/Core/NLS_API_Export.h")
target_include_directories(NamelessLib PUBLIC ${NLSLIB_INCLUDE_DIRS} ${VENDOR_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIR})
target_compile_definitions(NamelessLib PUBLIC GLFW_INCLUDE_NONE)
target_link_libraries(NamelessLib tinyxml2)
target_link_libraries(NamelessLib glfw)
target_link_libraries(NamelessLib ${Vulkan_LIBRARIES})
target_link_libraries(NamelessLib NamelessLogger)
