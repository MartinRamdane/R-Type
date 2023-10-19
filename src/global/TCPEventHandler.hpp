/*
** EPITECH PROJECT, 2023
** EventHandler.hpp
** File description:
** EventHandler
*/

#ifndef HEADER_TCPEventHandler
#define HEADER_TCPEventHandler
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>

enum class TCPACTION : uint8_t
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
  CREATEINSTANCE
};

struct TCPEvent
{
  TCPACTION ACTION_NAME;
  int body_size;
  std::string body;
};

class TCPEventHandler
{
public:
  TCPEventHandler() = default;
  TCPEventHandler(TCPACTION ACTION_NAME, int body_size, std::string body);
  ~TCPEventHandler();
  std::vector<uint8_t> encodeMessage();
  TCPEvent decodeMessage(std::vector<uint8_t> data);
  void addEvent(TCPACTION ACTION_NAME, int body_size, std::string body);
  int getRequestId() const { return _body_size; };
  const std::string getBody() const { return _body; };
  const TCPEvent getEvent() const { return TCPEvent{_ACTION_NAME, _body_size, _body}; };

protected:
private:
  TCPACTION _ACTION_NAME;
  int _body_size;
  std::string _body;
};

#endif /* !HEADER_TCPEventHandler */