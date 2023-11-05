/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientImpl
*/

#include "TCPClientImpl.hpp"
#include "Game.hpp"
#include "InstanceMenu.hpp"

void TCPClientImpl::HandleMessage(message<ACTION>& msg) {
    switch (msg.header.id) {
        case ACTION::CREATE: {
            try {
                EventHandler evt;
                evt.decodeMessage(msg.body);
                std::stringstream ss(evt.getBody());
                std::string playerId;
                std::string getPort;
                ss >> playerId;
                ss >> getPort;
                ss >> getPort;
                // add get windows
                int port = std::stoi(getPort);
                std::string serverToJoinInfos = std::to_string(port);
                Event evtToSend = {ACTION::JOIN, serverToJoinInfos};
                _game->getClient().get()->SendEvent(evtToSend);
                // TODO : Interepereter réponse de création d'instance -> Connecter au serveur UDP de l'instance du coup
            } catch (std::exception& e) {}
            break;
        }
        case ACTION::LIST: {
            try {
                EventHandler evt;
                evt.decodeMessage(msg.body);
                std::stringstream ss(evt.getBody());
                std::string instanceName;
                std::string instanceGameName;
                std::string instanceNbPlayers;
                std::string instanceMaxPlayers;
                std::string instancePort;
                std::string instanceId;
                ss >> instanceName;
                ss >> instanceGameName;
                ss >> instanceNbPlayers;
                ss >> instanceMaxPlayers;
                ss >> instancePort;
                ss >> instanceId;
                int nbPlayers = std::stoi(instanceNbPlayers);
                int maxPlayers = std::stoi(instanceMaxPlayers);
                int port = std::stoi(instancePort);
                int id = std::stoi(instanceId);
                InstanceType instance = {instanceName, instanceGameName,
                                         nbPlayers,    maxPlayers,
                                         port,         id};
                _game->getInstanceMenu()->addInstanceButton(instance, 0, 0);
            } catch (std::exception& e) {}
            break;
        }
        case ACTION::JOIN: {
            break;
        }
        case ACTION::JOINED: {
            try {
                EventHandler evt;
                evt.decodeMessage(msg.body);
                std::stringstream ss(evt.getBody());
                std::string playerId;
                std::string getPort;
                ss >> playerId;
                ss >> getPort;
                _game->setPlayerId(std::stoi(playerId));
                _game->connectToUdpServer(_game->getHost(), std::stoi(getPort));
            } catch (std::exception& e) {}
            break;
        }
        case ACTION::READY: {
            break;
        }
        case ACTION::LEFT: {
            break;
        }
        case ACTION::RIGHT: {
            break;
        }
        case ACTION::UP: {
            break;
        }
        case ACTION::DOWN: {
            break;
        }
        case ACTION::SPACE: {
            break;
        }
        case ACTION::QUIT: {
            break;
        }
        case ACTION::PING: {
            break;
        }
        case ACTION::PONG: {
            break;
        }
        case ACTION::SPRITE: {
            break;
        }
        case ACTION::UNKNOWN: {
            break;
        }
        case ACTION::TEXT: {
            break;
        }
        case ACTION::DEAD: {
            break;
        }
        case ACTION::FLIP: {
            break;
        }
        case ACTION::RESET: {
            break;
        }
        case ACTION::CHECK: {
            break;
        }
        case ACTION::SOUND: {
            break;
        }
        case ACTION::KEY: {
            break;
        }
    }
}