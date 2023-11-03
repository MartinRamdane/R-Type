#include "engine/Core.hpp"
#include "server/Server.hpp"
#include "global/EventHandler.hpp"

int main() {
    // TODO: Deprecated
    /*if (argc != 2) {
        std::cerr << "Usage: ./server <game> (r-type or pong)" << std::endl;
        return 1;
    } else {
        if (std::string(argv[1]) != "rType" && std::string(argv[1]) != "pong") {
            std::cerr << "Usage: ./server <game> (rType or pong)" << std::endl;
            return 1;
        }
    }*/
    EventHandler handler;
    uint32_t compressedCrc = handler.calculateCRCForInt(6);
    uint32_t originalCrc = handler.calculateCRCForInt(5);
    uint32_t actionCrc = handler.calculateCRCForAction(ACTION::CREATE);
    std::cout << "compressedCrc : " << compressedCrc << std::endl;
    std::cout << "originalCrc : " << originalCrc << std::endl;
    std::cout << "actionCrc : " << actionCrc << std::endl;
    handler.addEvent(ACTION::CREATE, "test");
    std::vector<uint8_t> data = handler.encodeMessage();
    Event evt = handler.decodeMessage(data);
    try {
        ServerClass server;
        server.loop();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
