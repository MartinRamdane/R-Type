/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane [WSL: Debian]
** File description:
** ServerImpl
*/

#ifndef SERVERIMPL_HPP_
#define SERVERIMPL_HPP_
#include "TCPServer.hpp"
#include "Server.hpp"

class MyServer : public TCPServer<ACTION>
{
    public:
        MyServer(int port, ServerClass *_server) : TCPServer<ACTION>(port), _server(_server) {}
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
    private :
    ServerClass *_server;
};

#endif /* !SERVERIMPL_HPP_ */
