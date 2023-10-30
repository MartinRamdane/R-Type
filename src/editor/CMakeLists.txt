file(GLOB EDITOR_SRC_LIST src/editor/*.cpp src/client/SFML/*.cpp src/global/*.cpp)
add_executable(r-type_editor ${EDITOR_SRC_LIST})

if (MSVC)
    target_link_options(r-type_editor PRIVATE /PROFILE)
endif()

target_include_directories(r-type_editor PRIVATE ${SFML_INCLUDE_DIR})
target_link_libraries(r-type_editor sfml-graphics sfml-audio sfml-window sfml-system nlohmann_json::nlohmann_json boost::boost LZ4::lz4_static)

set_target_properties(r-type_editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../
)