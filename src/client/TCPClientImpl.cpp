/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientImpl
*/

#include "TCPClientImpl.hpp"
#include "Game.hpp"

void TCPClientImpl::HandleMessage(message<ACTION> &msg)
{
  switch (msg.header.id)
  {
  case ACTION::CONNECT:
  {
    EventHandler evt;
    evt.decodeMessage(msg.body);
    std::cout << "[BODY DATA : ]" << evt.getBody() << std::endl;
  }
  break;
  case ACTION::CREATE:
  {
    EventHandler evt;
    evt.decodeMessage(msg.body);
    std::cout << "[BODY DATA]: " << evt.getBody() << std::endl;
    std::stringstream ss(evt.getBody());
    std::string playerId;
    std::string getPort;
    ss >> playerId;
    ss >> getPort;
    ss >> getPort;
    // add get windows infos
    int port = std::stoi(getPort);
    std::cout << "target port " << port << std::endl;
    std::cout << "target host " << _game->getHost() << std::endl;
    _game->connectToUdpServer(_game->getHost(), port);
    _game->setPlayerId(std::stoi(playerId));
    // TODO : Interepereter réponse de création d'instance -> Connecter au serveur UDP de l'instance du coup
  }
  break;
  case ACTION::LIST:
  {
  }
  break;
  case ACTION::JOIN:
  {
  }
  break;
  case ACTION::JOINED:
  {
  }
  break;
  case ACTION::READY:
  {
  }
  break;
  case ACTION::START:
  {
  }
  break;
  case ACTION::LEFT:
  {
  }
  break;
  case ACTION::RIGHT:
  {
  }
  break;
  case ACTION::UP:
  {
  }
  break;
  case ACTION::DOWN:
  {
  }
  break;
  case ACTION::SHOOT:
  {
  }
  break;
  case ACTION::QUIT:
  {
  }
  break;
  case ACTION::PING:
  {
  }
  break;
  case ACTION::PONG:
  {
  }
  break;
  case ACTION::OK:
  {
  }
  break;
  case ACTION::KO:
  {
  }
  case ACTION::SPRITE:
  {
  }
  case ACTION::UNKNOWN:
  {
  }
  case ACTION::SHIELD:
  {
  }
  break;
  }
}