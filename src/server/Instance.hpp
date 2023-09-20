/*
** EPITECH PROJECT, 2023
** Instance
** File description:
** Instance.hpp
*/

#ifndef HEADER_INSTANCE
  #define HEADER_INSTANCE
#include <iostream>
#include "EventHandler.hpp"

class Instance {
  public:
    Instance(int id);
    ~Instance();
    void getEventRequest(int requestId, std::string event);

  protected:
  private:
    int _id;
    EventHandler _eventHandler;
};

#endif /* !HEADER_INSTANCE */
