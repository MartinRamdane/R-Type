/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySDL.hpp
*/

#pragma once
#include "IDisplay.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "RessourceManager.hpp"
#include "TCPClientImpl.hpp"
#include "UDPClient.hpp"

class DisplaySDL : public IDisplay {
 public:
  DisplaySDL();
  ~DisplaySDL();
  void createWindow(std::string name, int x, int y);
//   void animate(std::map<int, Entity>* _entities);
//   void draw(std::map<int, Entity>* _entities);
//   void handleEvent(UDPClient* _udpClient, TCPClientImpl* _client);
//   void update(std::map<int, Entity>* _entities, UDPClient* _udpClient);
//   void run(std::map<int, Entity>* _entities, UDPClient* _udpClient,
//            TCPClientImpl* _client);
//   bool getClosed() const { return closed; };
//   void setPlayerId(int id) { _playerId = id; };
//   int getPlayerId() const { return _playerId; };
//   bool windowIsOpen() const { return _window.isOpen(); };

 private:
  SDL_Window* window;
  SDL_Renderer* renderer;

  int _event_indicator;
  std::chrono::high_resolution_clock::time_point _lastFrameTime;
  bool closed = false;
  int _playerId;
};