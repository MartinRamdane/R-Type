cmake_minimum_required(VERSION 3.12)

project(R_type)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)


file(GLOB SRC_LIST src/*.cpp src/server/*.cpp)

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

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    target_link_options(${PROJECT_NAME} PRIVATE)
endif()
find_package(asio REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${asio_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${asio_LIBRARIES})
