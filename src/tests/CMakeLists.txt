file(GLOB TEST_SRC_LIST src/tests/*.cpp src/engine/*.cpp src/engine/r-type/*.cpp src/global/*.cpp src/client/*.cpp src/client/SFML/*.cpp src/client/SDL/*.cpp src/server/*.cpp src/engine/pong/*.cpp)
list(REMOVE_ITEM TEST_SRC_LIST src/client/main.cpp)

foreach(item ${TEST_SRC_LIST})
    if(${item} MATCHES "client/main.cpp")
        list(REMOVE_ITEM TEST_SRC_LIST ${item})
    endif()
endforeach()

add_executable(r-type_test ${TEST_SRC_LIST})

target_link_libraries(r-type_test sfml-graphics sfml-audio sfml-window sfml-system SDL2::SDL2main SDL2::SDL2-static SDL2_image::SDL2_image-static SDL2_ttf::SDL2_ttf-static nlohmann_json::nlohmann_json boost::boost gtest::gtest LZ4::lz4_static)
