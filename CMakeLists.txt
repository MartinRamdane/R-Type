cmake_minimum_required(VERSION 3.16)

project(r-type_server)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(nlohmann_json REQUIRED)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3")
endif (UNIX)
file(GLOB SRC_LIST src/*.cpp src/server/*.cpp src/GameEngine/*.cpp src/GameEngine/r-type/*.cpp)

set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build the project
add_custom_target(run
    COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SRC_LIST})

# Specify the output directory for the binary
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

# For Windows, apply /FORCE:MULTIPLE linker option
if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    target_link_options(${PROJECT_NAME} PRIVATE)
endif()
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
find_package(Boost REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE boost::boost)
