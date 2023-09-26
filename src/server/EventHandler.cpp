/*
** EPITECH PROJECT, 2023
** EventHandler
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler(ACTION ACTION_NAME, int body_size, std::string event)
{
  addEvent(ACTION_NAME, body_size, event);
  std::cout << "[DEBUG] Event created: " << _body_size << " " << _event << std::endl;
}

EventHandler::~EventHandler()
{
}

std::vector<uint8_t> EventHandler::encodeMessage()
{
  std::vector<uint8_t> data(sizeof(ACTION) + sizeof(int) + _event.size());
  memcpy(data.data(), &_ACTION_NAME, sizeof(ACTION));
  memcpy(data.data() + sizeof(ACTION), &_body_size, sizeof(int));
  memcpy(data.data() + sizeof(ACTION) + sizeof(int), _event.data(), _event.size());
  return data;
}

Event EventHandler::decodeMessage(std::vector<uint8_t> data)
{
  Event event;
  std::memcpy(&event.ACTION_NAME, data.data(), sizeof(ACTION));
  std::memcpy(&event.body_size, data.data() + sizeof(ACTION), sizeof(int));
  event.event = std::string(reinterpret_cast<const char*>(data.data() + sizeof(ACTION) + sizeof(int)),
  data.size() - sizeof(ACTION) - sizeof(int));
  std::cout << "[DEBUG] Event decoded: " << event.body_size << " " << event.event << std::endl;
  return event;
}

void EventHandler::addEvent(ACTION ACTION_NAME, int body_size, std::string event)
{
  _ACTION_NAME = ACTION_NAME;
  _body_size = body_size;
  _event = event;
}