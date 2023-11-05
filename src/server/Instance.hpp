/*
** EPITECH PROJECT, 2023
** Instance.hpp
** File description:
** Instance
*/

#ifndef HEADER_INSTANCE
#define HEADER_INSTANCE

#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include "../engine/Core.hpp"
#include "../global/JsonParser.hpp"
#include "../global/ThreadPool.hpp"
#include "UDPServer.hpp"

class ServerClass;

class Instance {
   public:
    Instance(int _id, std::string gameName);

    Instance(const Instance&) = delete;

    ~Instance();  // destroy the instance if nbPlayers === 0
    int getId() const { return _id; }

    UDPServer* getUDPServer() { return _udpServer; }

    void setServer(ServerClass* server) { _serverRef = server; }

    int getNbPlayers() const { return _udpServer->getNbPlayers(); }

    int getMaxPlayers() const { return _nbPlayersMax; }

    int getPort() const { return _port; }

    std::string getName() const { return _name; }

    std::string getGameName() const { return _gameName; }

    Core* getCore() { return _core; }

    void MessagesLoop();

    void EventLoop();

    void addAction(Event event) { _events.push_back(event); }

    void checkEntitiesInClients();

    int getPlayerIdToGive() { return _playerIdToGive; }

    void setPlayerIdToGive(int id) { _playerIdToGive = id; }

   protected:
   private:
    int _id;
    int _port;
    int _nbPlayersMax;
    bool _onlyMultiplayer;
    std::string _name;
    std::string _gameName;
    boost::asio::io_service _io_service;
    UDPServer* _udpServer;
    ServerClass* _serverRef;
    ThreadPool _threadPool;
    Core* _core;
    ThreadSafeQueue<Event> _events;
    JsonParser _jsonParser;
    std::chrono::high_resolution_clock::time_point _lastCheck;
    bool _isRunning;
    int _playerIdToGive;
};

#endif /* !HEADER_INSTANCE */
