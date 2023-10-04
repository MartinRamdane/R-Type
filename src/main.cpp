#include "engine/Core.hpp"
#include "server/Server.hpp"

int main()
{
    ServerClass server;
    server.loop();
    return 0;
}
