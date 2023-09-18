cmake_minimum_required(VERSION 3.12)

project(R_type)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
# Include the Conan-generated toolchain file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)


# Gather all source files recursively
file(GLOB SRC_LIST Client/GameEngine/*.cpp)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SRC_LIST})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
endif (UNIX)
find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)

# Set the C++ standard to C++17

# Specify the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the project
add_custom_target(run
    COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# For Windows, apply /FORCE:MULTIPLE linker option
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
