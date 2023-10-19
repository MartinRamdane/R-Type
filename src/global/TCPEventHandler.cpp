/*
** EPITECH PROJECT, 2023
** EventHandler
** File description:
** EventHandler.cpp
*/

#include "TCPEventHandler.hpp"


TCPEventHandler::TCPEventHandler(TCPACTION ACTION_NAME, int body_size, std::string event)
{
  addEvent(ACTION_NAME, body_size, event);
}

TCPEventHandler::~TCPEventHandler()
{
}

std::vector<uint8_t> TCPEventHandler::encodeMessage()
{
  std::vector<uint8_t> data(sizeof(TCPACTION) + sizeof(int) + _body.size());
  memcpy(data.data(), &_ACTION_NAME, sizeof(TCPACTION));
  memcpy(data.data() + sizeof(TCPACTION), &_body_size, sizeof(int));
  memcpy(data.data() + sizeof(TCPACTION) + sizeof(int), _body.data(), _body.size());
  return data;
}

TCPEvent TCPEventHandler::decodeMessage(std::vector<uint8_t> data)
{
  TCPEvent event;
  std::memcpy(&event.ACTION_NAME, data.data(), sizeof(TCPACTION));
  std::memcpy(&event.body_size, data.data() + sizeof(TCPACTION), sizeof(int));
  event.body = std::string(reinterpret_cast<const char *>(data.data() + sizeof(TCPACTION) + sizeof(int)),
                           data.size() - sizeof(TCPACTION) - sizeof(int));
  event.body.resize(event.body_size);
  // std::cout << "[DEBUG] Event decoded: " << event.body_size << " " << event.body << std::endl;
  _body_size = event.body_size;
  _body = event.body;
  return event;
}

void TCPEventHandler::addEvent(TCPACTION ACTION_NAME, int body_size, std::string body)
{
  _ACTION_NAME = ACTION_NAME;
  _body_size = body_size;
  _body = body;
}