/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** IDisplay.hpp
*/

#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <map>
#include <memory>

class UDPClient;
class TCPClientImpl;
class Entity;

class IDisplay {
 public:
  IDisplay() = default;
  virtual ~IDisplay() = default;
  virtual void createWindow(std::string name, int x, int y) = 0;
  virtual void animate(std::map<int, Entity>* _entities) = 0;
  virtual void draw(std::map<int, Entity>* _entities) = 0;
  virtual void handleEvent(UDPClient* _udpClient, TCPClientImpl* _client) = 0;
  virtual void update(std::map<int, Entity>* _entities,
                      UDPClient* _udpClient) = 0;
  virtual void run(std::map<int, Entity>* _entities, UDPClient* _udpClient,
                   TCPClientImpl* _client) = 0;
  virtual void setPlayerId(int id) = 0;
  virtual int getPlayerId() const = 0;
  virtual bool getClosed() const = 0;
  virtual sf::RenderWindow& getWindow() const = 0;
  virtual bool windowIsOpen() const = 0;
};