/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.hpp
*/

#pragma once
#include <map>
#include <sstream>
#include "IEntity.hpp"
#include "Parser.hpp"
#include "../global/JsonParser.hpp"
#include "../global/EventHandler.hpp"
#include <thread>
#include <queue>
#include "UDPClient.hpp"
#include "../global/ThreadPool.hpp"
#include "ProgressBar.hpp"
#include <mutex>
// #include <concurrent_vector.h>
class TCPClientImpl;
class IDisplay;

class Game
{
public:
    enum Lib
    {
        SDL,
        SFML,
    };
    Game();
    ~Game(){};
    void run();
    void getinfos(){};
    bool connectToServer(std::string host, int port);
    bool connectToUdpServer(std::string host, int port);
    void setConnected(bool state) { isTCPClientConnected = state; };
    void setUDPConnected(bool state) { isUDPClientConnected = state; };
    void setGameTitle(std::string gameTitle) { _gameTitle = gameTitle; };
    void setWidth(int width) { _width = width; };
    void setHeight(int height) { _height = height; };
    bool findEntity(int id);
    void addEntity(IEntity::EntityInfos entityInfos);
    void removeEntity(int id);
    void LoopUDPMessages();
    void setPlayerId(int id);
    std::string getHost() { return _host; };
    TCPClientImpl *getClient() { return _client; };
    void flipEntity(Event evt);
    void clearEntities() { _entities.clear(); };
    Lib getLib() const { return _lib; };
    void setLib(int lib);
    void setLibToUse();
    void handleReceivedEvent(Event evt);
    void updateSprite(Event evt);
    void updateText(Event evt);
    void joinGame(Event evt);
    void loopEventQueue();

private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Clock _clock;
    TCPClientImpl *_client;
    UDPClient *_udpClient;
    int _event_indicator;
    std::queue<std::vector<uint8_t>> _queue;
    ThreadPool _threadPool;
    bool isTCPClientConnected = false;
    bool isUDPClientConnected = false;
    bool closed;
    std::string _gameTitle;
    int _width;
    int _height;
    std::map<int, std::shared_ptr<IEntity>> _entities;
    int _playerId;
    std::string _host;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    ProgressBar _progressBar;
    std::shared_ptr<IDisplay> _display;
    Lib _lib;
    std::mutex entityMutex;
    std::vector<int> _entitiesToRemove;
    Parser parseRef;
};
