#include "engine/Core.hpp"
#include "server/Server.hpp"

int main() {
    // TODO: Deprecated
    /*if (argc != 2) {
        std::cerr << "Usage: ./server <game> (r-type or pong)" << std::endl;
        return 1;
    } else {
        if (std::string(argv[1]) != "r-type" && std::string(argv[1]) != "pong") {
            std::cerr << "Usage: ./server <game> (r-type or pong)" << std::endl;
            return 1;
        }
    }*/
    try {
        ServerClass server;
        server.loop();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
