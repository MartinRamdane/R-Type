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

class ServerClass;    // Forward declaration
struct InstanceInfos; // Forward declaration

class MyServer : public TCPServer<TCPACTION>
{
public:
    MyServer(int port, ServerClass *_server) : TCPServer<TCPACTION>(port), _server(_server) {}
    void SendEvent(std::shared_ptr<TCPConnection<TCPACTION>> client, TCPEvent evt)
    {
        message<TCPACTION> msg;
        std::vector<uint8_t> data = encodeEvent(evt);
        msg.header.id = evt.ACTION_NAME;
        msg.header.size = sizeof(data);
        msg.body.resize(sizeof(data));
        std::memcpy(msg.body.data(), data.data(), sizeof(data));
        SendMessageAsync(client, msg);
    }
    std::vector<uint8_t> encodeEvent(TCPEvent event)
    {
        TCPEventHandler evt;
        evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
        return evt.encodeMessage();
    }

protected:
    virtual void OnMessage(std::shared_ptr<TCPConnection<TCPACTION>> client, message<TCPACTION> &msg)
    {
        switch (msg.header.id)
        {
        case TCPACTION::CONNECT:
        {
            TCPEventHandler evt;
            evt.decodeMessage(msg.body);
        }
        break;
        case TCPACTION::CREATEINSTANCE:
        {
            if (_server->getInstancesNb() >= 1) {
                Instance *instance = _server->getInstance(0);
                TCPEvent evt;
                evt.ACTION_NAME = TCPACTION::CREATEINSTANCE;
                int playerId = _server->getPlayerIdToGive();
                evt.body = std::to_string(_server->getPlayerIdToGive()) + " " + std::to_string(instance->getId()) + " " + std::to_string(instance->getPort());
                std::string playerEntityId = "p" + std::to_string(playerId);
                _server->setPlayerIdToGive(_server->getPlayerIdToGive() + 1);
                evt.body_size = evt.body.size();
                SendEvent(client, evt);
                return;
            }
            InstanceInfos infos = _server->createInstance();
            Instance *instance = _server->getInstance(_server->getInstancesNb() - 1);
            TCPEvent evt;
            evt.ACTION_NAME = TCPACTION::CREATEINSTANCE;
            int playerId = _server->getPlayerIdToGive();
            evt.body = std::to_string(_server->getPlayerIdToGive()) + " " + std::to_string(infos.id) + " " + std::to_string(infos.port);
            std::string playerEntityId = "p" + std::to_string(playerId);
            _server->setPlayerIdToGive(_server->getPlayerIdToGive() + 1);
            evt.body_size = evt.body.size();
            std::cout << "Sending to client: " << evt.body << std::endl;
            std::cout << "size : " << evt.body_size << std::endl;
            SendEvent(client, evt);
        }
        break;
        case TCPACTION::LIST:
        {
            std::cout << "[" << client->GetID() << "]: LIST" << std::endl;
        }
        break;
        case TCPACTION::JOIN:
        {
            std::cout << "[" << client->GetID() << "]: JOIN" << std::endl;
        }
        break;
        case TCPACTION::JOINED:
        {
            std::cout << "[" << client->GetID() << "]: JOINED" << std::endl;
        }
        break;
        case TCPACTION::READY:
        {
            std::cout << "[" << client->GetID() << "]: READY" << std::endl;
        }
        break;
        case TCPACTION::START:
        {
            std::cout << "[" << client->GetID() << "]: START" << std::endl;
        }
        break;
        case TCPACTION::LEFT:
        {
            std::cout << "[" << client->GetID() << "]: LEFT" << std::endl;
        }
        break;
        case TCPACTION::RIGHT:
        {
            std::cout << "[" << client->GetID() << "]: RIGHT" << std::endl;
        }
        break;
        case TCPACTION::UP:
        {
            std::cout << "[" << client->GetID() << "]: UP" << std::endl;
        }
        break;
        case TCPACTION::DOWN:
        {
            std::cout << "[" << client->GetID() << "]: DOWN" << std::endl;
        }
        break;
        case TCPACTION::SHOOT:
        {
            std::cout << "[" << client->GetID() << "]: SHOOT" << std::endl;
        }
        break;
        case TCPACTION::QUIT:
        {
            std::cout << "[" << client->GetID() << "]: QUIT" << std::endl;
        }
        break;
        case TCPACTION::PING:
        {
            std::cout << "[" << client->GetID() << "]: PING" << std::endl;
        }
        break;
        case TCPACTION::PONG:
        {
            std::cout << "[" << client->GetID() << "]: PONG" << std::endl;
        }
        break;
        case TCPACTION::OK:
        {
            std::cout << "[" << client->GetID() << "]: OK" << std::endl;
        }
        break;
        case TCPACTION::KO:
        {
            std::cout << "[" << client->GetID() << "]: KO" << std::endl;
        }
        break;
        case TCPACTION::UNKNOWN:
        {
            std::cout << "[" << client->GetID() << "]: UNKNOWN" << std::endl;
        }
        break;
        case TCPACTION::SPRITE:
        {
            std::cout << "[" << client->GetID() << "]: SPRITE" << std::endl;
        }
        break;
        case TCPACTION::SHIELD:
        {
            std::cout << "[" << client->GetID() << "]: SHIELD" << std::endl;
        }
        break;
        case TCPACTION::DEAD:
        {
            std::cout << "[" << client->GetID() << "]: DEAD" << std::endl;
        }
        case TCPACTION::FLIP:
        {
            std::cout << "[" << client->GetID() << "]: FLIP" << std::endl;
        }
        case TCPACTION::TEXT:
        {
            std::cout << "[" << client->GetID() << "]: TEXT" << std::endl;
        }
        case TCPACTION::RESET:
        {
            std::cout << "[" << client->GetID() << "]: RESET" << std::endl;
        }
        break;
        }
    }

private:
    ServerClass *_server;
};

#endif /* !SERVERIMPL_HPP_ */
