cmake_minimum_required(VERSION 3.12)

project(R_type)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
# Include the Conan-generated toolchain file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Find and link to the ZLIB library
find_package(ZLIB REQUIRED)

# Gather all source files recursively
file(GLOB SRC_LIST src/*.cpp)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Specify the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the project
add_custom_target(run
    COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# For Windows, apply /FORCE:MULTIPLE linker option
if (WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE)
endif()
