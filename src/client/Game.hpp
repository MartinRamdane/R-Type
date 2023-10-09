/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.hpp
*/

#pragma once
#include <map>
#include <sstream>
#include "Entity.hpp"
#include "RessourceManager.hpp"
#include "Parser.hpp"
#include "JsonParser.hpp"
#include "TCPClientImpl.hpp"
#include "../global/EventHandler.hpp"
#include <thread>
#include <queue>
#include "UDPClient.hpp"
#include "ThreadPool.hpp"
class TCPClientImpl;
class Game
{
public:
    Game();
    ~Game(){};
    void run();
    void createWindow(std::string name, int x, int y);
    void animate();
    void draw();
    void handleEvent();
    void update();
    void getinfos(){};
    bool connectToServer(std::string host, int port);
    bool connectToUdpServer(std::string host, int port);
    void setConnected(bool) { isTCPClientConnected = true; }
    void setUDPConnected(bool state) { isUDPClientConnected = state; }
    void setGameTitle(std::string gameTitle) { _gameTitle = gameTitle; }
    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }
    RessourceManager getRessourceManager() const { return _ressourceManager; }
    bool findEntity(int id);
    void addEntity(int id, Entity entity);
    void removeEntity(int);
    void LoopUDPMessages();
    void setPlayerId(int id) { _playerId = id; }

private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    sf::Clock _clock;
    RessourceManager _ressourceManager;
    TCPClientImpl *_client;
    UDPClient *_udpClient;
    int _event_indicator;
    std::queue<std::vector<uint8_t>> _queue;
    ThreadPool _threadPool;
    // bool isInstanceConnected = false;
    bool isTCPClientConnected = false;
    bool isUDPClientConnected = false;
    bool closed;
    std::string _gameTitle;
    int _width;
    int _height;
    std::map<int, Entity> _entities;
    int _playerId;
};
