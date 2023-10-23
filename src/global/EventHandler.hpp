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
#include <memory>
#include "DataCompress.hpp"

enum class ACTION : uint8_t
{
  OK,
  KO,
  CONNECT,
  CREATE,
  LIST,
  JOIN,
  JOINED,
  READY,
  START,
  LEFT,
  RIGHT,
  UP,
  DOWN,
  SHOOT,
  QUIT,
  PING,
  PONG,
  SPRITE,
  TEXT,
  SHIELD,
  DEAD,
  FLIP,
  RESET,
  UNKNOWN,
};

struct Event
{
  ACTION ACTION_NAME;
  int compressed_size;
  int original_size;
  std::string body;
};

class EventHandler
{
public:
  EventHandler() = default;
  EventHandler(ACTION ACTION_NAME, int compressed_size, int original_size, std::string body);
  ~EventHandler();
  std::vector<uint8_t> encodeMessage();
  Event decodeMessage(std::vector<uint8_t> data);
  void addEvent(ACTION ACTION_NAME, int compressed_size, int original_size, std::string body);
  const std::string getBody() const { return _body; };
  const Event getEvent() const { return Event{_ACTION_NAME, _compressed_size, _original_size, _body}; };

protected:
private:
  ACTION _ACTION_NAME;
  int _compressed_size;
  int _original_size;
  std::string _body;
};

#endif /* !HEADER_EVENTHANDLER */