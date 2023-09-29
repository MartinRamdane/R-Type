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

class MyServer : public TCPServer<ACTION>
{
    public:
        MyServer(int port) : TCPServer<ACTION>(port) {}
    protected:
        virtual void OnMessage(std::shared_ptr<TCPConnection<ACTION>> client, message<ACTION>& msg) {
            switch (msg.header.id)
            {
            case ACTION::CONNECT:
            {
                std::cout << "[" << client->GetID() << "]: CONNECT" << std::endl;
                EventHandler evt;
                evt.decodeMessage(msg.body);
                std::cout << "[BODY DATA : ]" << evt.getEvent() << std::endl;
            }
            break;
            case ACTION::CREATE:
            {
                std::cout << "[" << client->GetID() << "]: CREATE" << std::endl;
            }
            break;
            case ACTION::LIST:
            {
                std::cout << "[" << client->GetID() << "]: LIST" << std::endl;
            }
            break;
            case ACTION::JOIN:
            {
                std::cout << "[" << client->GetID() << "]: JOIN" << std::endl;
            }
            break;
            case ACTION::JOINED:
            {
                std::cout << "[" << client->GetID() << "]: JOINED" << std::endl;
            }
            break;
            case ACTION::READY:
            {
                std::cout << "[" << client->GetID() << "]: READY" << std::endl;
            }
            break;
            case ACTION::START:
            {
                std::cout << "[" << client->GetID() << "]: START" << std::endl;
            }
            break;
            case ACTION::LEFT:
            {
                std::cout << "[" << client->GetID() << "]: LEFT" << std::endl;
            }
            break;
            case ACTION::RIGHT:
            {
                std::cout << "[" << client->GetID() << "]: RIGHT" << std::endl;
            }
            break;
            case ACTION::UP:
            {
                std::cout << "[" << client->GetID() << "]: UP" << std::endl;
            }
            break;
            case ACTION::DOWN:
            {
                std::cout << "[" << client->GetID() << "]: DOWN" << std::endl;
            }
            break;
            case ACTION::SHOOT:
            {
                std::cout << "[" << client->GetID() << "]: SHOOT" << std::endl;
            }
            break;
            case ACTION::QUIT:
            {
                std::cout << "[" << client->GetID() << "]: QUIT" << std::endl;
            }
            break;
        }
    }

};

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
        MyServer server(4243);
        server.StartServer();
        while (1) {
            server.HandleMessages(-1, true);
        }
    }
    else if (ac == 2)
    {
        MyClient c;
        c.Connect("127.0.0.1", 4243);
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