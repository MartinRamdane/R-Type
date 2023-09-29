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

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};


class MyServer : public TCPServer<CustomMsgTypes>
{
    public:
        MyServer(int port) : TCPServer<CustomMsgTypes>(port) {}
    protected:

};

class MyClient : public TCPClient<CustomMsgTypes>
{
    public:
        void PingServer() {
            message<CustomMsgTypes> msg;
            msg.header.id = CustomMsgTypes::ServerPing;
            std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();
            msg.body.resize(sizeof(std::chrono::system_clock::time_point));
            std::memcpy(msg.body.data(), &timeNow, sizeof(std::chrono::system_clock::time_point));
            Send(msg);
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
            server.HandleMessages(-1);
        }
    }
    else if (ac == 2)
    {
        MyClient c;
        c.Connect("127.0.0.1", 4243);
        while (1) {
            if (c.isConnected()) {
                c.PingServer();
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