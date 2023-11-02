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

  // Copy the event data into the vector
  std::memcpy(data.data(), &event.ACTION_NAME, sizeof(ACTION));
  std::memcpy(data.data() + sizeof(ACTION), &event.original_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int), &event.compressed_size, sizeof(int));
  std::memcpy(data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), event.body, event.compressed_size);

  // Calculate CRC for the data and append it to the end
  uint32_t crc = calculateCRC(data);
  data.insert(data.end(), reinterpret_cast<uint8_t*>(&crc), reinterpret_cast<uint8_t*>(&crc) + sizeof(uint32_t));

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
    if (static_cast<unsigned int>(netevt.ACTION_NAME) < 0U || static_cast<unsigned int>(netevt.ACTION_NAME) > 25U)
      throw std::runtime_error("Invalid ACTION");
    if (netevt.compressed_size < 0 || netevt.original_size < 0)
      throw std::runtime_error("Invalid size");
    netevt.body = new char[netevt.compressed_size];
    if (netevt.body == NULL) {
      throw std::runtime_error("Not enough memory");
    }
    if (static_cast<unsigned int>(netevt.compressed_size) > data.size() - sizeof(ACTION) - sizeof(int) - sizeof(int)) {
      delete[] netevt.body;
      throw std::runtime_error("Packet has been corrupted");
    }
    uint32_t receivedCRC;
    std::memcpy(&receivedCRC, data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int) + netevt.compressed_size, sizeof(uint32_t));

    // Calculate CRC for the data (excluding the received CRC)
    std::vector<uint8_t> dataWithoutCRC(data.begin(), data.end() - sizeof(uint32_t));
    uint32_t calculatedCRC = calculateCRC(dataWithoutCRC);

    if (receivedCRC != calculatedCRC) {
      throw std::runtime_error("CRC check failed");
    }
    std::memcpy(netevt.body, data.data() + sizeof(ACTION) + sizeof(int) + sizeof(int), netevt.compressed_size);
     if (netevt.compressed_size < 0 || netevt.original_size < 0) {
      delete[] netevt.body;
      throw std::runtime_error("Packet has been corrupted");
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
    char *decompressed = decompressor.Decompress(netevt.body);
    decompressed[decompressor.getOriginalSize() - 1] = '\0';
    Event event;
    event.ACTION_NAME = netevt.ACTION_NAME;
    event.body = std::string(decompressed);
    _body = std::string(decompressed);
    _ACTION_NAME = netevt.ACTION_NAME;
    _body_size = netevt.original_size;
    delete[] netevt.body;
    if (netevt.original_size > decompressor.getOriginalSize()){
      delete decompressed;
      throw std::runtime_error("Decompression failed 1");
    }
    return event;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    throw std::runtime_error("Decompression failed 2");
  } catch (...) {
    throw std::runtime_error("Decompression failed 3");
  }
}

void EventHandler::addEvent(ACTION ACTION_NAME, std::string body)
{
  _ACTION_NAME = ACTION_NAME;
  _body = body;
}