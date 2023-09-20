/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id) : _id(id)
{
}

Instance::~Instance()
{
}

void Instance::getEventRequest(int requestId, std::string event)
{
  _eventHandler.addEvent(requestId, event);
  std::cout << "[DEBUG] Event created in Instance: " << _eventHandler.getRequestId() << " " << _eventHandler.getEvent() << std::endl;
}