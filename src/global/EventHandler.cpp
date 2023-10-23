/*
** EPITECH PROJECT, 2023
** EventHandler
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler(ACTION ACTION_NAME, int compressed_size, int original_size, std::string body)
{
  addEvent(ACTION_NAME, compressed_size, original_size, body);
}

EventHandler::~EventHandler()
{
}

std::vector<uint8_t> EventHandler::encodeMessage()
{
  std::vector<uint8_t> data(sizeof(ACTION) + sizeof(int) + sizeof(int) + _body.size());
  std::memcpy(data.data(), &_ACTION_NAME, sizeof(ACTION));
  std::memcpy(data.data() + sizeof(ACTION), &_compressed_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int), &_original_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), _body.c_str(), _body.size());

  return data;
}

Event EventHandler::decodeMessage(std::vector<uint8_t> data)
{
  Event event;
  std::memcpy(&event.ACTION_NAME, data.data(), sizeof(ACTION));
  std::memcpy(&event.compressed_size, data.data() + sizeof(ACTION), sizeof(int));
  std::memcpy(&event.original_size, data.data() + sizeof(ACTION) + sizeof(int), sizeof(int));
  event.body = std::string(reinterpret_cast<const char *>(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int)),
  data.size() - sizeof(ACTION) - sizeof(int) - sizeof(int));
  _ACTION_NAME = event.ACTION_NAME;
  _compressed_size = event.compressed_size;
  _original_size = event.original_size;
  _body = event.body;
  DataCompress decompressor(event.compressed_size, event.original_size);
  event.body = std::string(decompressor.Decompress(event.body.c_str()));
  return event;
}

void EventHandler::addEvent(ACTION ACTION_NAME, int compressed_size, int original_size, std::string body)
{
  _ACTION_NAME = ACTION_NAME;
  _compressed_size = compressed_size;
  _original_size = original_size;
  _body = body;
}