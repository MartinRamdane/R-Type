cmake_minimum_required(VERSION 3.12)

project(r-type_client)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
# Include the Conan-generated toolchain file
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)


# Gather all source files recursively
file(GLOB SRC_LIST Client/*.cpp)

# Create an executable from the source files
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3 -lstdc++fs -std=c++17")
endif (UNIX AND NOT APPLE)
add_executable(${PROJECT_NAME} ${SRC_LIST})
find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)
find_package(boost REQUIRED)
find_package(nlohmann_json REQUIRED)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

# Build the project
add_custom_target(run
    COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
include(CheckCXXSymbolExists)
check_cxx_symbol_exists(std::filesystem::path::preferred_separator filesystem cxx17fs)
target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} boost::boost)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system  ${asio_LIBRARIES} nlohmann_json::nlohmann_json)
