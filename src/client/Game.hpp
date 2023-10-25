/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.hpp
*/

#pragma once
#include <map>
#include <queue>
#include <sstream>
#include <thread>
#include <vector>
#include "../global/EventHandler.hpp"
#include "../global/JsonParser.hpp"
#include "../global/ThreadPool.hpp"
#include "../types/Instance.hpp"
#include "Entity.hpp"
#include "Parser.hpp"
#include "ProgressBar.hpp"
#include "RessourceManager.hpp"
#include "UDPClient.hpp"

class TCPClientImpl;
class IDisplay;

class Game {
   public:
    Game();
    ~Game(){};
    void run();
    void createWindow(std::string name, int x, int y);
    void getinfos(){};
    bool connectToServer(std::string host, int port);
    bool connectToUdpServer(std::string host, int port);
    void setConnected(bool state) { isTCPClientConnected = state; }
    void setUDPConnected(bool state) { isUDPClientConnected = state; }
    void setGameTitle(std::string gameTitle) { _gameTitle = gameTitle; }
    void setWidth(int width) { _width = width; }
    void setHeight(int height) { _height = height; }
    RessourceManager getRessourceManager() const { return _ressourceManager; }
    bool findEntity(int id);
    void addEntity(int id, Entity entity);
    void removeEntity(int);
    void LoopUDPMessages();
    void setPlayerId(int id);
    std::string getHost() { return _host; }
    TCPClientImpl* getClient() { return _client; }
    void flipEntity(int id);
    void clearEntities() { _entities.clear(); }

   private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    sf::Clock _clock;
    RessourceManager _ressourceManager;
    TCPClientImpl* _client;
    UDPClient* _udpClient;
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
    std::string _host;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    ProgressBar _progressBar;
    std::shared_ptr<IDisplay> _display;
    std::vector<InstanceType> _instances;
};
