/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <iostream>
#include <boost/asio.hpp>
#include "../global/EventHandler.hpp"

class Game;

class UDPClient
{
public:
  UDPClient();
  ~UDPClient();
  void send_data(const std::string &data, const std::string &host, int port);
  void connect_to(const std::string &host, int port);
  void setGameRef(Game *gameRef);
  void receive_data();
  bool check_ping(const std::string &data);
  void sendEvent(Event evt, const std::string &host, int port);
  std::vector<uint8_t> encodeEvent(Event event);
  std::string getHost() const { return _host; }
  int getPort() const { return _port; }

private:
  boost::asio::io_context io_context_;
  boost::asio::ip::udp::socket socket_;
  std::string _host;
  std::vector<uint8_t> recv_buffer_ = std::vector<uint8_t>(1024);
  int _port;
  Game *_gameRef;
};

#endif /* !UDPCLIENT_HPP_ */