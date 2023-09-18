cmake_minimum_required(VERSION 3.12)

project(R_type)
if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
find_package(ZLIB REQUIRED)
file(GLOB_RECURSE SOURCES *.cpp)

add_executable(MyExecutable ${SOURCES})
set(CMAKE_CXX_STANDARD 11)

# For Windows:
if (WIN32)
    set(CMAKE_GENERATOR "Visual Studio 17 2022")
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
    set(CMAKE_CONFIGURATION_TYPES "Release")

    # Specify the output folder for the binary
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    # Build the project
    add_custom_target(run
        COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
   add_custom_command(TARGET run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/bin/${PROJECT_NAME}.exe"
        "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.exe"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
else()
    # For other platforms:
    set(CMAKE_BUILD_TYPE Release)

    # Build the project
    add_custom_target(run
        COMMAND cmake --build ${CMAKE_BINARY_DIR} --config Release
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    add_custom_command(TARGET run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/${PROJECT_NAME}"
        "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
