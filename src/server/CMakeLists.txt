file(GLOB SERVER_SRC_LIST src/*.cpp src/server/*.cpp src/engine/*.cpp src/engine/r-type/*.cpp src/global/*.cpp src/engine/pong/*.cpp)
add_executable(r-type_server ${SERVER_SRC_LIST})

if (MSVC)
    target_link_options(r-type_server PRIVATE /PROFILE)
endif()

target_link_libraries(r-type_server PRIVATE nlohmann_json::nlohmann_json boost::boost LZ4::lz4_static)
