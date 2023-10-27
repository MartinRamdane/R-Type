/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySFML.hpp
*/

#pragma once
#include "../IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "RessourceManager.hpp"
#include "../TCPClientImpl.hpp"
#include "../UDPClient.hpp"

class DisplaySFML : public IDisplay {
 public:
  DisplaySFML();
  ~DisplaySFML();
  void createWindow(std::string name, int x, int y);
  void animate(std::map<int, std::shared_ptr<IEntity>> *_entities);
  void draw(std::map<int, std::shared_ptr<IEntity>> *_entities);
  void handleEvent(UDPClient* _udpClient, TCPClientImpl* _client);
  void update(std::map<int, std::shared_ptr<IEntity>> *_entities, UDPClient* _udpClient);
  bool getClosed() const { return closed; };
  void setPlayerId(int id) { _playerId = id; };
  int getPlayerId() const { return _playerId; };
  bool windowIsOpen() const { return _window.isOpen(); };
  std::shared_ptr<IEntity> createEntity(IEntity::EntityInfos entityInfos);
  std::shared_ptr<IEntity> createSprite(IEntity::EntityInfos entityInfos);
  std::shared_ptr<IEntity> createText(IEntity::EntityInfos entityInfos);

 private:
  sf::RenderWindow _window;
  sf::View _view;
  sf::Event _event;
  std::shared_ptr<RessourceManager> _ressourceManager;
  int _eventIndicator;
  std::chrono::high_resolution_clock::time_point _lastFrameTime;
  bool closed = false;
  int _playerId;
};