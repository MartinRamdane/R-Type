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
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)
find_package(lz4 REQUIRED)

if (UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -g3")
endif (UNIX)

if (WIN32)
    # Set debug information flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")

    # Other profiling flags (if needed)
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /PGD:profile_data.pgd")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /PGD:profile_data.pgd")
endif (WIN32)
file(GLOB CLIENT_SRC_LIST src/client/*.cpp src/client/SFML/*.cpp src/global/*.cpp)
add_executable(r-type_client ${CLIENT_SRC_LIST})
if (MSVC)
  target_link_options(r-type_client PRIVATE /PROFILE)
endif()
target_include_directories(r-type_client PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})
target_include_directories(r-type_client PRIVATE ${SDL2_INCLUDE_DIRS})
target_include_directories(r-type_client PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(r-type_client sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json boost::boost SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static LZ4::lz4_static)

file(GLOB SERVER_SRC_LIST src/*.cpp src/server/*.cpp src/engine/*.cpp src/engine/r-type/*.cpp src/global/*.cpp src/engine/pong/*.cpp)
add_executable(r-type_server ${SERVER_SRC_LIST})
target_link_libraries(r-type_server PRIVATE nlohmann_json::nlohmann_json boost::boost LZ4::lz4_static)

file(GLOB TEST_SRC_LIST src/tests/*.cpp src/engine/*.cpp src/engine/r-type/*.cpp src/global/*.cpp src/client/*.cpp src/client/SFML/*.cpp src/server/*.cpp src/engine/pong/*.cpp)
if (MSVC)
  target_link_options(r-type_server PRIVATE /PROFILE)
endif()
list(REMOVE_ITEM TEST_SRC_LIST src/client/main.cpp)
foreach(item ${TEST_SRC_LIST})
    if(${item} MATCHES "client/main.cpp")
        list(REMOVE_ITEM TEST_SRC_LIST ${item})
    endif()
endforeach()
add_executable(r-type_test ${TEST_SRC_LIST})
target_link_libraries(r-type_test sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json boost::boost gtest::gtest SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static LZ4::lz4_static)

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