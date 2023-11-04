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
#include <boost/crc.hpp>

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
  SPACE,
  QUIT,
  PING,
  PONG,
  SPRITE,
  TEXT,
  DEAD,
  FLIP,
  RESET,
  UNKNOWN,
  CHECK,
  SOUND,
  KEY
};

struct Event
{
  ACTION ACTION_NAME;
  std::string body;
};

struct NetworkEvent
{
  ACTION ACTION_NAME;
  int original_size;
  int compressed_size;
  char *body;
};

class EventHandler
{
public:
  EventHandler() = default;
  EventHandler(ACTION ACTION_NAME, std::string body);
  ~EventHandler();
  std::vector<uint8_t> encodeMessage();
  Event decodeMessage(std::vector<uint8_t> data);
  void addEvent(ACTION ACTION_NAME, std::string body);
  const std::string getBody() const { return _body; };
  const Event getEvent() const { return Event{_ACTION_NAME, _body}; };
  uint32_t calculateCRCForInt(int value) {
    boost::crc_32_type result;
    result.process_bytes(&value, sizeof(int));
    return result.checksum();
  }
  uint32_t calculateCRCForAction(ACTION action) {
    boost::crc_32_type result;
    result.process_bytes(&action, sizeof(ACTION));
    return result.checksum();
  }
  uint32_t calculateCRCForBody(const char *body, int size) {
    boost::crc_32_type result;
    result.process_bytes(body, size);
    return result.checksum();
  }
protected:
private:
  ACTION _ACTION_NAME;
  int _body_size;
  std::string _body;
};

#endif /* !HEADER_EVENTHANDLER */