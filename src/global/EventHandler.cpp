/*
** EPITECH PROJECT, 2023
** EventHandler
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler(ACTION ACTION_NAME, std::string event)
{
  addEvent(ACTION_NAME, event);
}

EventHandler::~EventHandler()
{
}

std::vector<uint8_t> EventHandler::encodeMessage()
{
  NetworkEvent event;
  event.ACTION_NAME = _ACTION_NAME;
  event.body_size = _body.size();
  event.body = const_cast<char *>(_body.c_str());
  std::vector<uint8_t> data(sizeof(ACTION) + sizeof(int) + event.body_size);
  std::memcpy(data.data(), &event.ACTION_NAME, sizeof(ACTION));
  std::memcpy(data.data() + sizeof(ACTION), &event.body_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int), event.body, event.body_size);
  return data;
}

Event EventHandler::decodeMessage(std::vector<uint8_t> data)
{
  NetworkEvent netevt;
  std::memcpy(&netevt.ACTION_NAME, data.data(), sizeof(ACTION));
  std::memcpy(&netevt.body_size, data.data() + sizeof(ACTION), sizeof(int));
  std::string body = std::string(reinterpret_cast<const char *>(data.data() + sizeof(ACTION) + sizeof(int)),
  data.size() - sizeof(ACTION) - sizeof(int));
  body.resize(netevt.body_size);
  netevt.body = const_cast<char *>(body.c_str());
  Event event;
  event.ACTION_NAME = netevt.ACTION_NAME;
  event.body = body;
  _body = body;
  _ACTION_NAME = netevt.ACTION_NAME;
  return event;
}

void EventHandler::addEvent(ACTION ACTION_NAME, std::string body)
{
  _ACTION_NAME = ACTION_NAME;
  _body = body;
}