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

std::vector<char> EventHandler::encodeMessage()
{
  std::vector<char> data(sizeof(ACTION) + sizeof(int) + _event.size());
  memcpy(data.data(), &_ACTION_NAME, sizeof(ACTION));
  memcpy(data.data() + sizeof(ACTION), &_body_size, sizeof(int));
  memcpy(data.data() + sizeof(ACTION) + sizeof(int), _event.data(), _event.size());
  return data;
}

Event EventHandler::decodeMessage(std::vector<char> data)
{
  Event event;
  memcpy(&event.ACTION_NAME, data.data(), sizeof(ACTION));
  memcpy(&event.body_size, data.data() + sizeof(ACTION), sizeof(int));
  event.event = std::string(data.data() + sizeof(ACTION) + sizeof(int), data.size() - sizeof(ACTION) - sizeof(int));
  return event;
}

void EventHandler::addEvent(ACTION ACTION_NAME, int body_size, std::string event)
{
  _ACTION_NAME = ACTION_NAME;
  _body_size = body_size;
  _event = event;
}