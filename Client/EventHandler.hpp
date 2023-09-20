/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** EventHandler.hpp
*/

#ifndef HEADER_EVENTHANDLER
#define HEADER_EVENTHANDLER
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

struct Event
{
  int requestId;
  std::string event;
};

class EventHandler
{
  public:
    EventHandler() = default;
    EventHandler(int requestId, std::string event);
    ~EventHandler();
    std::vector<char> encodeMessage();
    Event decodeMessage(std::vector<char> data);
    void addEvent(int requestId, std::string event);
    int getRequestId() const { return _requestId; };
    std::string getEvent() const { return _event; };

  protected:
  private:
    int _requestId;
    std::string _event;
};

#endif /* !HEADER_EVENTHANDLER */