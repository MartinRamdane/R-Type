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

class MyServer : public TCPServer<ACTION> {
public:
    MyServer(int port, ServerClass *_server) : TCPServer<ACTION>(port), _server(_server) {}

    void SendEvent(std::shared_ptr <TCPConnection<ACTION>> client, Event evt) {
        message<ACTION> msg;
        std::vector <uint8_t> data = encodeEvent(evt);
        msg.header.id = evt.ACTION_NAME;
        msg.header.size = data.size();
        msg.body.resize(data.size());
        std::memcpy(msg.body.data(), data.data(), data.size());
        SendMessageAsync(client, msg);
    }

    std::vector <uint8_t> encodeEvent(Event event) {
        EventHandler evt;
        evt.addEvent(event.ACTION_NAME, event.body);
        return evt.encodeMessage();
    }

protected:
    virtual void OnMessage(std::shared_ptr <TCPConnection<ACTION>> client, message<ACTION> &msg) {
        switch (msg.header.id) {
            case ACTION::CREATE: {
                try {
                    EventHandler handler;
                    handler.decodeMessage(msg.body);
                    std::stringstream ss(handler.getBody());
                    std::string gameName;
                    ss >> gameName;
                    InstanceInfos infos = _server->createInstance(gameName);
                    Instance *instance = _server->getInstance(_server->getInstancesNb() - 1);
                    Event evt;
                    evt.ACTION_NAME = ACTION::JOINED;
                    int playerId = instance->getPlayerIdToGive();
                    evt.body = std::to_string(instance->getPlayerIdToGive()) + " " + std::to_string(infos.port);
                    std::string playerEntityId = "p" + std::to_string(playerId);
                    instance->getUDPServer()->addPlayerEntity(playerId, playerEntityId);
                    instance->setPlayerIdToGive(instance->getPlayerIdToGive() + 1);
                    SendEvent(client, evt);
                } catch (std::exception &e) {
                }
            }
                break;
            case ACTION::LIST: {
                try {
                    std::cout << "[" << client->GetID() << "]: LIST" << std::endl;
                    Event evt = {ACTION::LIST, ""};
                    for (auto instance: _server->getInstances()) {
                        if (instance->getNbPlayers() == 1)
                            continue;
                        evt.body = instance->getName() + " " + instance->getGameName() + " " +
                                   std::to_string(instance->getNbPlayers() - 1) + " " +
                                   std::to_string(instance->getMaxPlayers()) + " " + std::to_string(instance->getPort()) +
                                   " " + std::to_string(instance->getId());
                        SendEvent(client, evt);
                    }
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
            case ACTION::JOIN: {
                try {
                    std::cout << "[" << client->GetID() << "]: JOIN" << std::endl;
                    EventHandler handler;
                    handler.decodeMessage(msg.body);
                    std::stringstream ss(handler.getBody());
                    std::string port;
                    ss >> port;
                    Instance *instance = _server->getInstanceByPort(std::stoi(port));
                    if (instance == nullptr) {
                        std::cerr << "[ERROR]: Bad instance to join" << std::endl;
                        return;
                    }
                    Event evt;
                    evt.ACTION_NAME = ACTION::JOINED;
                    int playerId = instance->getPlayerIdToGive();
                    evt.body = std::to_string(instance->getPlayerIdToGive()) + " " + port;
                    std::string playerEntityId = "p" + std::to_string(playerId);
                    instance->getUDPServer()->addPlayerEntity(playerId, playerEntityId);
                    instance->setPlayerIdToGive(instance->getPlayerIdToGive() + 1);
                    SendEvent(client, evt);
                } catch (std::exception &e) {
                }
            }
                break;
            case ACTION::JOINED: {
                std::cout << "[" << client->GetID() << "]: JOINED" << std::endl;
            }
                break;
            case ACTION::READY: {
                std::cout << "[" << client->GetID() << "]: READY" << std::endl;
            }
                break;
            case ACTION::LEFT: {
                std::cout << "[" << client->GetID() << "]: LEFT" << std::endl;
            }
                break;
            case ACTION::RIGHT: {
                std::cout << "[" << client->GetID() << "]: RIGHT" << std::endl;
            }
                break;
            case ACTION::UP: {
                std::cout << "[" << client->GetID() << "]: UP" << std::endl;
            }
                break;
            case ACTION::DOWN: {
                std::cout << "[" << client->GetID() << "]: DOWN" << std::endl;
            }
                break;
            case ACTION::SPACE: {
                std::cout << "[" << client->GetID() << "]: SPACE" << std::endl;
            }
                break;
            case ACTION::QUIT: {
                std::cout << "[" << client->GetID() << "]: QUIT" << std::endl;
                std::cout << "quit event" << std::endl;
                EventHandler handler;
                handler.decodeMessage(msg.body);
                std::stringstream ss(handler.getBody());
                std::string host;
                std::string portString;
                ss >> host;
                ss >> portString;
                int port = std::stoi(portString);
                Instance *instance = _server->getInstanceByPort(port);
                if (instance == nullptr) {
                    std::cerr << "[ERROR]: Bad instance to quit" << std::endl;
                    return;
                }
                int nbPlayers = instance->getNbPlayers();
                instance->getUDPServer()->setNbPlayers(nbPlayers - 1);
                if (instance->getNbPlayers() == 1) {
                    std::cout << "delete instance" << std::endl;
                    _server->deleteInstance(instance->getId());
                }
            }
                break;
            case ACTION::PING: {
                std::cout << "[" << client->GetID() << "]: PING" << std::endl;
            }
                break;
            case ACTION::PONG: {
                std::cout << "[" << client->GetID() << "]: PONG" << std::endl;
            }
                break;
            case ACTION::UNKNOWN: {
                std::cout << "[" << client->GetID() << "]: UNKNOWN" << std::endl;
            }
                break;
            case ACTION::SPRITE: {
                std::cout << "[" << client->GetID() << "]: SPRITE" << std::endl;
            }
                break;
            case ACTION::DEAD: {
                std::cout << "[" << client->GetID() << "]: DEAD" << std::endl;
            }
            case ACTION::FLIP: {
                std::cout << "[" << client->GetID() << "]: FLIP" << std::endl;
            }
            case ACTION::TEXT: {
                std::cout << "[" << client->GetID() << "]: TEXT" << std::endl;
            }
            case ACTION::RESET: {
                std::cout << "[" << client->GetID() << "]: RESET" << std::endl;
            }
            case ACTION::CHECK: {
                std::cout << "[" << client->GetID() << "]: CHECK" << std::endl;
            }
            case ACTION::SOUND: {
                std::cout << "[" << client->GetID() << "]: SOUND" << std::endl;
            }
            default:
                break;
        }
    }
}

private:
    ServerClass *_server;
};

#endif /* !SERVERIMPL_HPP_ */
