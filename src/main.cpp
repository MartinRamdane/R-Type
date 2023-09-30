#include <iostream>
#include "Player.hpp"
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

class MyClient : public TCPClient<ACTION>
{
    public:
        void SendEvent(Event evt) {
            message<ACTION> msg;
            std::vector<uint8_t> data = encodeEvent(evt);
            msg.header.id = evt.ACTION_NAME;
            msg.header.size = sizeof(data);
            msg.body.resize(sizeof(data));
            std::memcpy(msg.body.data(), data.data(), sizeof(data));
            Send(msg);
        }
        std::vector<uint8_t> encodeEvent(Event event) {
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
        ServerClass server;
        server.loop();

    }
    else if (ac == 2)
    {
        MyClient c;
        c.Connect("127.0.0.1", 4244);
        Event evt;
        evt.ACTION_NAME = ACTION::CONNECT;
        evt.body_size = 3;
        evt.body = "slt";
        while (1) {
            if (c.isConnected()) {
                c.SendEvent(evt);
            }
        }
        return 0;
    } else {
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