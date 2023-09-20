/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler(int requestId, std::string event)
{
  addEvent(requestId, event);
  std::cout << "[DEBUG] Event created: " << _requestId << " " << _event << std::endl;
}

EventHandler::~EventHandler()
{
}

std::vector<char> EventHandler::encodeMessage()
{
  std::vector<char> data(sizeof(int) + _event.size());
  memcpy(data.data(), &_requestId, sizeof(int));
  memcpy(data.data() + sizeof(int), _event.data(), _event.size());
  return data;
}

Event EventHandler::decodeMessage(std::vector<char> data)
{
  Event event;
  memcpy(&event.requestId, data.data(), sizeof(int));
  event.event = std::string(data.data() + sizeof(int), data.size() - sizeof(int));
  return event;
}

void EventHandler::addEvent(int requestId, std::string event)
{
  _requestId = requestId;
  _event = event;
}