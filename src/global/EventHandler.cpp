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
  DataCompress compressor;
  char *compressed = compressor.Compress(_body.c_str());
  NetworkEvent event;
  event.ACTION_NAME = _ACTION_NAME;
  event.original_size = compressor.getOriginalSize();
  event.compressed_size = compressor.getCompressedSize();
  event.body = compressed;
  std::vector<uint8_t> data(sizeof(ACTION) + sizeof(int) + sizeof(int) + event.compressed_size);
  std::memcpy(data.data(), &event.ACTION_NAME, sizeof(ACTION));
  std::memcpy(data.data() + sizeof(ACTION), &event.original_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int), &event.compressed_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), event.body, event.compressed_size);
  return data;
}

Event EventHandler::decodeMessage(std::vector<uint8_t> data)
{
  NetworkEvent netevt;
  std::memcpy(&netevt.ACTION_NAME, data.data(), sizeof(ACTION));
  std::memcpy(&netevt.original_size, data.data() + sizeof(ACTION), sizeof(int));
  std::memcpy(&netevt.compressed_size, data.data() + sizeof(ACTION) + sizeof(int), sizeof(int));
  netevt.body = new char[netevt.compressed_size];
  std::memcpy(netevt.body, data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), netevt.compressed_size);
  if (netevt.compressed_size == 0)
  {
    Event event;
    event.ACTION_NAME = netevt.ACTION_NAME;
    event.body = "";
    _body = "";
    _ACTION_NAME = netevt.ACTION_NAME;
    return event;
  }
  DataCompress decompressor(netevt.compressed_size, netevt.original_size);
  char *decompressed = decompressor.Decompress(netevt.body);
  decompressed[decompressor.getOriginalSize() - 1] = '\0';
  Event event;
  event.ACTION_NAME = netevt.ACTION_NAME;
  event.body = std::string(decompressed);
  _body = std::string(decompressed);
  _ACTION_NAME = netevt.ACTION_NAME;
  _body_size = netevt.original_size;
  delete[] netevt.body;
  return event;
}

void EventHandler::addEvent(ACTION ACTION_NAME, std::string body)
{
  _ACTION_NAME = ACTION_NAME;
  _body = body;
}