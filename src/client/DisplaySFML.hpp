/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySFML.hpp
*/

#pragma once
#include "IDisplay.hpp"
#include "RessourceManager.hpp"
#include "TCPClientImpl.hpp"
#include "UDPClient.hpp"

// mais zeb jetais pas dans la bonne classe
//mdrrrrrrr ptn j'avaic cette erreur aussi tout a l'heure quand j'ai mis class IDisplay dans GAme.hpp

class DisplaySFML : public IDisplay {
 public:
  DisplaySFML();
  ~DisplaySFML();
  void createWindow(std::string name, int x, int y);
  void animate(std::map<int, Entity>* _entities);
  void draw(std::map<int, Entity>* _entities);
  void handleEvent(UDPClient* _udpClient, TCPClientImpl* _client);
  void update(std::map<int, Entity>* _entities, UDPClient* _udpClient);
  void run(std::map<int, Entity>* _entities, UDPClient* _udpClient,
           TCPClientImpl* _client);
  bool getClosed() { return closed; };
  void setPlayerId(int id) { _playerId = id; };
  int getPlayerId() { return _playerId; };
  sf::RenderWindow& getWindow() { return _window; };
  bool windowIsOpen() { return _window.isOpen(); };

 protected:

 private:
  sf::RenderWindow _window;
  sf::View _view;
  sf::Event _event;
  RessourceManager _ressourceManager;
  int _event_indicator;
  std::chrono::high_resolution_clock::time_point _lastFrameTime;
  bool closed = false;
  int _playerId;
};