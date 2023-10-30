file(GLOB CLIENT_SRC_LIST src/client/*.cpp src/client/SFML/*.cpp src/global/*.cpp)
add_executable(r-type_client ${CLIENT_SRC_LIST})

if (MSVC)
    target_link_options(r-type_client PRIVATE /PROFILE)
endif()

target_include_directories(r-type_client PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(r-type_client PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(r-type_client sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json boost::boost LZ4::lz4_static)

set_target_properties(r-type_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)
