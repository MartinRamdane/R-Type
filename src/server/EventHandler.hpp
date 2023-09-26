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
#include <cstring>

enum ACTION
{
  OK,
  KO,
  CONNECT,
  CREATE,
  LIST,
  JOIN,
  JOINED,
  READY,
  START
};

struct Event
{
  ACTION ACTION_NAME;
  int body_size;
  std::string event;
};

class EventHandler
{
  public:
    EventHandler() = default;
    EventHandler(ACTION ACTION_NAME, int body_size, std::string event);
    ~EventHandler();
    std::vector<uint8_t> encodeMessage();
    Event decodeMessage(std::vector<uint8_t> data);
    void addEvent(ACTION ACTION_NAME, int body_size, std::string event);
    const int getRequestId() const { return _body_size; };
    const std::string getEvent() const { return _event; };

  protected:
  private:
    ACTION _ACTION_NAME;
    int _body_size;
    std::string _event;
};

#endif /* !HEADER_EVENTHANDLER */
