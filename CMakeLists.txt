cmake_minimum_required(VERSION 3.16)
project(r-type)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Global settings and package findings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)
find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3")
endif (UNIX)

file(GLOB CLIENT_SRC_LIST src/client/*.cpp src/global/*.cpp)
add_executable(r-type_client ${CLIENT_SRC_LIST})
target_include_directories(r-type_client PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(r-type_client sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json boost::boost)

file(GLOB SERVER_SRC_LIST src/*.cpp src/server/*.cpp src/engine/*.cpp src/engine/r-type/*.cpp src/global/*.cpp)
add_executable(r-type_server ${SERVER_SRC_LIST})
target_link_libraries(r-type_server PRIVATE nlohmann_json::nlohmann_json boost::boost)

file(GLOB TEST_SRC_LIST src/test/*.cpp src/engine/*.cpp src/engine/r-type/*.cpp src/global/*.cpp src/client/*.cpp src/server/*.cpp)
add_executable(r-type_test ${TEST_SRC_LIST})
target_link_libraries(r-type_test sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json boost::boost)

set_target_properties(r-type_client r-type_server r-type_test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

add_custom_target(run
    COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
    DEPENDS r-type_client r-type_server
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()
