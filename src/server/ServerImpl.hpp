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

class MyServer : public TCPServer<ACTION>
{
public:
    MyServer(int port, ServerClass *_server) : TCPServer<ACTION>(port), _server(_server) {}
    void SendEvent(std::shared_ptr<TCPConnection<ACTION>> client, Event evt)
    {
        message<ACTION> msg;
        std::vector<uint8_t> data = encodeEvent(evt);
        msg.header.id = evt.ACTION_NAME;
        msg.header.size = sizeof(data);
        msg.body.resize(sizeof(data));
        std::memcpy(msg.body.data(), data.data(), sizeof(data));
        SendMessageAsync(client, msg);
    }
    std::vector<uint8_t> encodeEvent(Event event)
    {
        EventHandler evt;
        evt.addEvent(event.ACTION_NAME, event.body);
        return evt.encodeMessage();
    }

protected:
    virtual void OnMessage(std::shared_ptr<TCPConnection<ACTION>> client, message<ACTION> &msg)
    {
        switch (msg.header.id)
        {
        case ACTION::CONNECT:
        {
            EventHandler evt;
            evt.decodeMessage(msg.body);
        }
        break;
        case ACTION::CREATE:
        {
            if (_server->getInstancesNb() >= 1) {
                Instance *instance = _server->getInstance(0);
                Event evt;
                evt.ACTION_NAME = ACTION::CREATE;
                int playerId = _server->getPlayerIdToGive();
                evt.body = std::to_string(_server->getPlayerIdToGive()) + " " + std::to_string(instance->getId()) + " " + std::to_string(instance->getPort());
                std::string playerEntityId = "p" + std::to_string(playerId);
                instance->getUDPServer()->addPlayerEntity(playerId, playerEntityId);
                _server->setPlayerIdToGive(_server->getPlayerIdToGive() + 1);
                SendEvent(client, evt);
                return;
            }
            InstanceInfos infos = _server->createInstance();
            Instance *instance = _server->getInstance(_server->getInstancesNb() - 1);
            Event evt;
            evt.ACTION_NAME = ACTION::CREATE;
            int playerId = _server->getPlayerIdToGive();
            evt.body = std::to_string(_server->getPlayerIdToGive()) + " " + std::to_string(infos.id) + " " + std::to_string(infos.port);
            std::string playerEntityId = "p" + std::to_string(playerId);
            instance->getUDPServer()->addPlayerEntity(playerId, playerEntityId);
            _server->setPlayerIdToGive(_server->getPlayerIdToGive() + 1);
            SendEvent(client, evt);
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
        case ACTION::SPACE:
        {
            std::cout << "[" << client->GetID() << "]: SPACE" << std::endl;
        }
        break;
        case ACTION::QUIT:
        {
            std::cout << "[" << client->GetID() << "]: QUIT" << std::endl;
        }
        break;
        case ACTION::PING:
        {
            std::cout << "[" << client->GetID() << "]: PING" << std::endl;
        }
        break;
        case ACTION::PONG:
        {
            std::cout << "[" << client->GetID() << "]: PONG" << std::endl;
        }
        break;
        case ACTION::OK:
        {
            std::cout << "[" << client->GetID() << "]: OK" << std::endl;
        }
        break;
        case ACTION::KO:
        {
            std::cout << "[" << client->GetID() << "]: KO" << std::endl;
        }
        break;
        case ACTION::UNKNOWN:
        {
            std::cout << "[" << client->GetID() << "]: UNKNOWN" << std::endl;
        }
        break;
        case ACTION::SPRITE:
        {
            std::cout << "[" << client->GetID() << "]: SPRITE" << std::endl;
        }
        break;
        case ACTION::KEY_S:
        {
            std::cout << "[" << client->GetID() << "]: KEY_S" << std::endl;
        }
        break;
        case ACTION::DEAD:
        {
            std::cout << "[" << client->GetID() << "]: DEAD" << std::endl;
        }
        case ACTION::FLIP:
        {
            std::cout << "[" << client->GetID() << "]: FLIP" << std::endl;
        }
        case ACTION::TEXT:
        {
            std::cout << "[" << client->GetID() << "]: TEXT" << std::endl;
        }
        case ACTION::RESET:
        {
            std::cout << "[" << client->GetID() << "]: RESET" << std::endl;
        }
        case ACTION::KEY_L:
        {
            std::cout << "[" << client->GetID() << "]: KEY_L" << std::endl;
        }
        break;
        }
    }

private:
    ServerClass *_server;
};

#endif /* !SERVERIMPL_HPP_ */
