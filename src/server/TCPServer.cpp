/*
** EPITECH PROJECT, 2023
** TCPServer.cpp
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

TCPServer::TCPServer(int port) : _acceptor(io_context_, tcp::endpoint(tcp::v4(), port))
{
  startAccept();
}

TCPServer::~TCPServer()
{
}
