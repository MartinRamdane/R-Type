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
  uint32_t bodyCrc = calculateCRCForBody(compressed, event.compressed_size);
  event.bodyCrc = bodyCrc;
  NetworkChecksum checksum;
  checksum.ACTION_NAME = _ACTION_NAME;
  checksum.original_size = compressor.getOriginalSize();
  checksum.compressed_size = compressor.getCompressedSize();
  checksum.bodyCrc = bodyCrc;
  uint32_t crc = calculateCRC(checksum);
  std::vector<uint8_t> data(sizeof(ACTION) + sizeof(int) + sizeof(int) + event.compressed_size + 2 * sizeof(uint32_t));
  // Copy the event data into the vector
  std::memcpy(data.data(), &event.ACTION_NAME, sizeof(ACTION));
  std::memcpy(data.data() + sizeof(ACTION), &event.original_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int), &event.compressed_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), event.body, event.compressed_size);
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int) + event.compressed_size, &bodyCrc, sizeof(uint32_t));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int) + event.compressed_size + sizeof(uint32_t), &crc, sizeof(uint32_t));
  // std::cout << "checksum got : " << crc << std::endl;
  return data;
}


Event EventHandler::decodeMessage(std::vector<uint8_t> data)
{
  try {
    NetworkEvent netevt;
    netevt.compressed_size = -1;
    netevt.original_size = -1;
    std::memcpy(&netevt.ACTION_NAME, data.data(), sizeof(ACTION));
    std::memcpy(&netevt.original_size, data.data() + sizeof(ACTION), sizeof(int));
    std::memcpy(&netevt.compressed_size, data.data() + sizeof(ACTION) + sizeof(int), sizeof(int));
    std::memcpy(&netevt.bodyCrc, data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int) + netevt.compressed_size, sizeof(uint32_t));
    NetworkChecksum checksum;
    checksum.ACTION_NAME = netevt.ACTION_NAME;
    checksum.original_size = netevt.original_size;
    checksum.compressed_size = netevt.compressed_size;
    checksum.bodyCrc = netevt.bodyCrc;
    if (data.size() < sizeof(ACTION) + 2 * sizeof(int) + netevt.compressed_size + 2 * sizeof(uint32_t)) {
      throw std::runtime_error("[ERROR] Packet has been corrupted. Not enought size of CRC");
    }
    netevt.body = new char[netevt.compressed_size];
    if (netevt.body == NULL) {
      throw std::runtime_error("[ERROR] Not enough memory");
    }
    if (static_cast<unsigned int>(netevt.compressed_size) > data.size() - sizeof(ACTION) - sizeof(int) - sizeof(int)) {
      delete[] netevt.body;
      throw std::runtime_error("[ERROR] Packet has been corrupted");
    }
    std::memcpy(netevt.body, data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), netevt.compressed_size);
    uint32_t getCRC = 0;
    uint32_t generateCRC = calculateCRC(checksum);
    std::memcpy(&getCRC, data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int) + netevt.compressed_size + sizeof(uint32_t), sizeof(uint32_t));
     if (getCRC != generateCRC)
      throw std::runtime_error("[ERROR] Packet has been corrupted CRC IS NOT VALID");
     if (netevt.compressed_size < 0 || netevt.original_size < 0) {
      delete[] netevt.body;
      throw std::runtime_error("[ERROR] Packet has been corrupted");
     }
     if (netevt.compressed_size == 0)
    {
      Event event;
      event.ACTION_NAME = netevt.ACTION_NAME;
      event.body = "";
      _body = "";
      _ACTION_NAME = netevt.ACTION_NAME;
      delete[] netevt.body;
      return event;
    }
    DataCompress decompressor(netevt.compressed_size, netevt.original_size);
    uint32_t compressedCRC = calculateCRCForBody(netevt.body, netevt.compressed_size);
    if (compressedCRC != netevt.bodyCrc)
    {
      delete[] netevt.body;
      throw std::runtime_error("Packet has been corrupted. CRC is not valid for body");
    }
    char *decompressed = decompressor.Decompress(netevt.body);
    decompressed[decompressor.getOriginalSize() - 1] = '\0';
    if (strlen(decompressed) != decompressor.getOriginalSize() - 1)
    {
      delete decompressed;
      delete[] netevt.body;
      throw std::runtime_error("[ERROR] Decoding failed");
    }
    Event event;
    event.ACTION_NAME = netevt.ACTION_NAME;
    event.body = std::string(decompressed);
    _body = std::string(decompressed);
    if (event.body.size() != decompressor.getOriginalSize() - 1)
    {
      delete decompressed;
      delete[] netevt.body;
      throw std::runtime_error("Decompression failed. Wrong size.");
    }
    _ACTION_NAME = netevt.ACTION_NAME;
    _body_size = netevt.original_size;
    delete[] netevt.body;
    if (netevt.original_size > decompressor.getOriginalSize()){
      delete decompressed;
      throw std::runtime_error("[ERROR] Decoding failed");
    }
    return event;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    throw std::runtime_error("[ERROR] Decoding failed");
  } catch (...) {
    throw std::runtime_error("[ERROR] Decoding failed");
  }
}

void EventHandler::addEvent(ACTION ACTION_NAME, std::string body)
{
  _ACTION_NAME = ACTION_NAME;
  _body = body;
}