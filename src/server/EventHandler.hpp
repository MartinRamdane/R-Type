/*
** EPITECH PROJECT, 2023
** EventHandler.hpp
** File description:
** EventHandler
*/

#ifndef HEADER_EVENTHANDLER
#define HEADER_EVENTHANDLER
#include <iostream>
#include <string>
#include <vector>

struct Event
{
  int requestId;
  std::string event;
};

class EventHandler
{
public:
  EventHandler(int requestId, std::string event);
  ~EventHandler();
  std::vector<char> encodeMessage();
  Event decodeMessage(std::vector<char> data);

protected:
private:
  int _requestId;
  std::string _event;
};

#endif /* !HEADER_EVENTHANDLER */
