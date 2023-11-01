cmake_minimum_required(VERSION 3.16)
project(r-type)

if (POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define build options
option(BUILD_CLIENT "Build the client" ON)
option(BUILD_SERVER "Build the server" ON)
option(BUILD_TESTS "Build the tests" ON)
option(BUILD_EDITOR "Build the editor" ON)

# Set the output directories for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Release)

# Find required packages
find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)
find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)
find_package(lz4 REQUIRED)
find_program(ZIP_TOOL zip)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3")
endif (UNIX)

if (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")
endif (WIN32)

# Include other CMake files for different targets based on build options
if (BUILD_CLIENT)
    include(src/client/CMakeLists.txt)
endif ()

if (BUILD_SERVER)
    include(src/server/CMakeLists.txt)
endif ()

if (BUILD_TESTS)
    include(src/tests/CMakeLists.txt)
endif ()

if (BUILD_EDITOR)
    include(src/editor/CMakeLists.txt)
endif ()

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif ()

# Check if options are deactivated
if (NOT BUILD_CLIENT)
    message(STATUS "Client build option is deactivated.")
endif ()

if (NOT BUILD_SERVER)
    message(STATUS "Server build option is deactivated.")
endif ()

if (NOT BUILD_TESTS)
    message(STATUS "Tests build option is deactivated.")
endif ()

if (NOT BUILD_EDITOR)
    message(STATUS "Editor build option is deactivated.")
endif ()