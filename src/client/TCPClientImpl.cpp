/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientImpl
*/

#include "TCPClientImpl.hpp"
#include "Game.hpp"

void TCPClientImpl::HandleMessage(message<TCPACTION> &msg)
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
            TCPEventHandler evt;
            evt.decodeMessage(msg.body);
            std::stringstream ss(evt.getBody());
            std::string playerId;
            std::string getPort;
            ss >> playerId;
            ss >> getPort;
            ss >> getPort;
            // add get windows infos
            int port = std::stoi(getPort);
            _game->connectToUdpServer(_game->getHost(), port);
            _game->setPlayerId(std::stoi(playerId));
            // TODO : Interepereter réponse de création d'instance -> Connecter au serveur UDP de l'instance du coup
        }
        break;
        case TCPACTION::LIST:
        {
        }
        break;
        case TCPACTION::JOIN:
        {
        }
        break;
        case TCPACTION::JOINED:
        {
        }
        break;
        case TCPACTION::READY:
        {
        }
        break;
        case TCPACTION::START:
        {
        }
        break;
        case TCPACTION::LEFT:
        {
        }
        break;
        case TCPACTION::RIGHT:
        {
        }
        break;
        case TCPACTION::UP:
        {
        }
        break;
        case TCPACTION::DOWN:
        {
        }
        break;
        case TCPACTION::SHOOT:
        {
        }
        break;
        case TCPACTION::QUIT:
        {
        }
        break;
        case TCPACTION::PING:
        {
        }
        break;
        case TCPACTION::PONG:
        {
        }
        break;
        case TCPACTION::OK:
        {
        }
        break;
        case TCPACTION::KO:
        {
        }
        case TCPACTION::SPRITE:
        {
        }
        case TCPACTION::UNKNOWN:
        {
        }
        case TCPACTION::SHIELD:
        {
        }
        break;
        case TCPACTION::TEXT:
        {
        }
        break;
        case TCPACTION::DEAD:
        {
        }
        case TCPACTION::FLIP:
        {
        }
        case TCPACTION::RESET:
        {
        }
        break;
    }
}