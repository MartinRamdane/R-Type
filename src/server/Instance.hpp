/*
** EPITECH PROJECT, 2023
** Instance.hpp
** File description:
** Instance
*/

#ifndef HEADER_INSTANCE
#define HEADER_INSTANCE
#include "UDPServer.hpp"

class Instance {
  public:
    Instance();
    ~Instance();

  protected:
  private:
  UDPServer _udpServer;
};

#endif /* !HEADER_INSTANCE */
