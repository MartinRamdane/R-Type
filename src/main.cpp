#include "engine/Core.hpp"
#include "server/Server.hpp"
#include "engine/r-type/map_editor/Editor.hpp"

int main(int argc, char* argv[]) {
    Editor editor;
    // if (argc != 2) {
    //     std::cerr << "Usage: ./server <game> (rType or pong)" << std::endl;
    //     return 1;
    // } else {
    //     if (std::string(argv[1]) != "rType" && std::string(argv[1]) != "pong") {
    //         std::cerr << "Usage: ./server <game> (rType or pong)" << std::endl;
    //         return 1;
    //     }
    // }
    // try {
    //     ServerClass server(argv[1]);
    //     server.loop();
    // } catch (std::exception& e) {
    //     std::cerr << e.what() << std::endl;
    // }
    // return 0;
}
