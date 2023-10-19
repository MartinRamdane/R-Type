/*
** EPITECH PROJECT, 2023
** EventHandler
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler(ACTION ACTION_NAME, int body_size, std::vector<uint8_t> event)
{
  addEvent(ACTION_NAME, body_size, event);
}

EventHandler::~EventHandler()
{
}

std::vector<uint8_t> EventHandler::encodeMessage()
{
    _body_size = _body.size();
  size_t totalSize = sizeof(ACTION) + sizeof(size_t) + _body_size;

  // Create a vector to store the binary representation
  std::vector<uint8_t> encodedData(totalSize);

  // Use memcpy to copy the struct members into the vector
  size_t offset = 0;

  memcpy(encodedData.data() + offset, &_ACTION_NAME, sizeof(ACTION));
  offset += sizeof(ACTION);

  memcpy(encodedData.data() + offset, &_body_size, sizeof(size_t));
  offset += sizeof(size_t);

  memcpy(encodedData.data() + offset, _body.data(), _body_size);
  //::cout << "event original size of vector data UDP : " << _body_size << std::endl;
  //std::cout << "action : " << actionToString(_ACTION_NAME) << std::endl;
  return encodedData;
}

Event EventHandler::decodeMessage(std::vector<uint8_t> data)
{
  Event event;

  // Use memcpy to copy data from the vector to the struct
  size_t offset = 0;

  memcpy(&event.ACTION_NAME, data.data() + offset, sizeof(ACTION));
  offset += sizeof(ACTION);

  memcpy(&event.body_size, data.data() + offset, sizeof(size_t));
  offset += sizeof(size_t);

  // Resize the body vector and copy data
  event.body.resize(event.body_size);
  memcpy(event.body.data(), data.data() + offset, event.body_size);
  _ACTION_NAME = event.ACTION_NAME;
  _body_size = event.body_size;
  _body = event.body;
  return event;
}

void EventHandler::addEvent(ACTION ACTION_NAME, int body_size, std::vector<uint8_t> body)
{
  _ACTION_NAME = ACTION_NAME;
  _body_size = body_size;
  _body = body;
}

std::string EventHandler::actionToString(ACTION action)
{
  switch (action)
  {
  case ACTION::OK:
      return "OK";
  case ACTION::KO:
      return "KO";
  case ACTION::CONNECT:
      return "CONNECT";
  case ACTION::CREATE:
      return "CREATE";
  case ACTION::LIST:
      return "LIST";
  case ACTION::JOIN:
      return "JOIN";
  case ACTION::JOINED:
      return "JOINED";
  case ACTION::READY:
      return "READY";
  case ACTION::START:
      return "START";
  case ACTION::LEFT:
      return "LEFT";
  case ACTION::RIGHT:
      return "RIGHT";
  case ACTION::UP:
      return "UP";
  case ACTION::DOWN:
      return "DOWN";
  case ACTION::SHOOT:
      return "SHOOT";
  case ACTION::QUIT:
      return "QUIT";
  case ACTION::PING:
      return "PING";
  case ACTION::PONG:
      return "PONG";
  case ACTION::SPRITE:
      return "SPRITE";
  case ACTION::UNKNOWN:
      return "UNKNOWN";
  case ACTION::SHIELD:
      return "SHIELD";
  case ACTION::TEXT:
      return "TEXT";
  case ACTION::DEAD:
      return "DEAD";
  case ACTION::FLIP:
      return "FLIP";
  case ACTION::RESET:
      return "RESET";
  case ACTION::MOVE:
      return "MOVE";
  case ACTION::WINDOW:
      return "WINDOW";
  case ACTION::CREATEINSTANCE:
      return "CREATEINSTANCE";
  }
  return "";
}