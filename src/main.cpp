#include "engine/Core.hpp"
#include "server/Server.hpp"

int main()
{
    try {
        ServerClass server;
        server.loop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;

}
