cmake_minimum_required(VERSION 3.16)
project(r-type_client  VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

find_package(SFML 2.6 COMPONENTS graphics audio window system REQUIRED)


add_executable(${PROJECT_NAME} Client/GameEngine/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
