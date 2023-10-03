#include "engine/Core.hpp"
#include "server/Server.hpp"

int main(int ac, char **av)
{
    ServerClass server;
    server.loop();
    return 0;
}
