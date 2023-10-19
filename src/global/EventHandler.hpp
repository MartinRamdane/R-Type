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
  MOVE,
  WINDOW,
  CREATEINSTANCE
};
// std::ostream& operator<<(std::ostream& os, const ACTION& action)
// {
//   switch (action) {
//     case ACTION::OK: os << "OK"; break;
//     case ACTION::KO: os << "KO"; break;
//     case ACTION::CONNECT: os << "CONNECT"; break;
//     case ACTION::CREATE: os << "CREATE"; break;
//     case ACTION::LIST: os << "LIST"; break;
//     case ACTION::JOIN: os << "JOIN"; break;
//     case ACTION::JOINED: os << "JOINED"; break;
//     case ACTION::READY: os << "READY"; break;
//     case ACTION::START: os << "START"; break;
//     case ACTION::LEFT: os << "LEFT"; break;
//     case ACTION::RIGHT: os << "RIGHT"; break;
//     case ACTION::UP: os << "UP"; break;
//     case ACTION::DOWN: os << "DOWN"; break;
//     case ACTION::SHOOT: os << "SHOOT"; break;
//     case ACTION::QUIT: os << "QUIT"; break;
//     case ACTION::PING: os << "PING"; break;
//     case ACTION::PONG: os << "PONG"; break;
//     case ACTION::SPRITE: os << "SPRITE"; break;
//     case ACTION::TEXT: os << "TEXT"; break;
//     case ACTION::SHIELD: os << "SHIELD"; break;
//     case ACTION::DEAD: os << "DEAD"; break;
//     case ACTION::FLIP: os << "FLIP"; break;
//     case ACTION::RESET: os << "RESET"; break;
//     case ACTION::UNKNOWN: os << "UNKNOWN"; break;
//     case ACTION::MOVE: os << "MOVE"; break;
//     case ACTION::WINDOW: os << "WINDOW"; break;
//     case ACTION::CREATEINSTANCE: os << "CREATEINSTANCE"; break;
//     default: os << "INVALID ACTION"; break;
//   }
//   return os;
// }
struct Event
{
  ACTION ACTION_NAME;
  size_t body_size;
  std::vector <uint8_t> body;
};

class EventHandler
{
public:
  EventHandler() = default;
  EventHandler(ACTION ACTION_NAME, int body_size, std::vector<uint8_t> body);
  ~EventHandler();
  std::vector<uint8_t> encodeMessage();
  Event decodeMessage(std::vector<uint8_t> data);
  void addEvent(ACTION ACTION_NAME, int body_size, std::vector<uint8_t> body);
  size_t  getRequestId() const { return _body_size; };
  const std::vector<uint8_t> getBody() const { return _body; };
  const Event getEvent() const { return Event{_ACTION_NAME, _body_size, _body}; };
  std::string actionToString(ACTION action);

protected:
private:
  ACTION _ACTION_NAME;
  size_t _body_size;
  std::vector<uint8_t> _body;
};

#endif /* !HEADER_EVENTHANDLER */