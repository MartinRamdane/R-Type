#include <iostream>
#include "server/UDPServer.hpp"
#include "server/UDPClient.hpp"
#include <thread>
#include <chrono>
#include "server/Server.hpp"
#include "server/TCPClient.hpp"
#include "server/TCPServer.hpp"
#include "server/Instance.hpp"
#include "server/EventHandler.hpp"
#include "server/UDPServer.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include "GameEngine/JsonParser.hpp"
#include "GameEngine/Core.hpp"

// int main()
// {
//     Core core;
//     core.mainLoop("test");
//     return 0;
// }

class MyClient : public TCPClient<ACTION>
{
public:
    void SendEvent(Event evt)
    {
        message<ACTION> msg;
        std::vector<uint8_t> data = encodeEvent(evt);
        msg.header.id = evt.ACTION_NAME;
        msg.header.size = sizeof(data);
        msg.body.resize(sizeof(data));
        std::memcpy(msg.body.data(), data.data(), sizeof(data));
        Send(msg);
    }
    std::vector<uint8_t> encodeEvent(Event event)
    {
        EventHandler evt;
        evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
        return evt.encodeMessage();
    }

protected:
};

int main(int ac, char **av)
{
    if (ac == 1)
    {
        // ServerClass server;
        // server.loop();
        Core core;
        core.mainLoop("test");
        return 0;
    }
    else if (ac == 2)
    {
        MyClient c;
        c.Connect("127.0.0.1", 4244);
        Event evt;
        evt.ACTION_NAME = ACTION::CONNECT;
        evt.body_size = 0;
        evt.body = "";
        c.SendEvent(evt);
        evt.ACTION_NAME = ACTION::CREATE;
        evt.body_size = 0;
        evt.body = "";
        c.SendEvent(evt);
        while (1)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        return 0;
    }
    else
    {
        std::cout << "av2: " << atoi(av[2]) << std::endl;
        UDPClient client;
        client.connect_to("127.0.0.1", atoi(av[2]));
        while (1)
        {
            std::string received_data = client.receive_data(); // TODO: foutre ça dans un thread non ??? Parce que c'est bloquant
            std::cout << "Received: " << received_data << std::endl;
        }
    }
}
