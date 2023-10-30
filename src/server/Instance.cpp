/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id, std::string gameName)
        : _id(id), _port((int) (4210 + id)), _gameName(gameName), _threadPool(3) {
    std::string gameConfigFilePathName = gameName + "InstanceConfig.json";
    _name = "toChange";
    nlohmann::json jsonFile = _jsonParser.readFile(gameConfigFilePathName);
    _nbPlayersMax = _jsonParser.get<int>(jsonFile, "nbPlayersMax");
    _onlyMultiplayer = _jsonParser.get<bool>(jsonFile, "onlyMultiplayer");
    std::cout << "nbplayersmax: " << _nbPlayersMax << " only multiplayer " << _onlyMultiplayer
              << std::endl;
    _udpServer = new UDPServer(_io_service, (int) (4210 + id));
    _udpServer->setNbPlayers(1);
    _core = new Core(gameName);
    _udpServer->setInstance(this);
    _threadPool.enqueue([this]() { _io_service.run(); });
    // implement the main loop in thread
    _threadPool.enqueue([this]() { MessagesLoop(); });
    _threadPool.enqueue([this]() { EventLoop(); });
}

Instance::~Instance() {}

void Instance::MessagesLoop() {
    while (1) {
        _udpServer->handleMessages(-1, true);
    }
}

void Instance::EventLoop() {
    while (1) {
        int nbPlayers = _udpServer->getNbPlayers();
        if (nbPlayers == 0) {
            continue;    // TODO: destroy the instance
        }
        if (_lastCheck.time_since_epoch().count() == 0) {
            _lastCheck = std::chrono::high_resolution_clock::now();
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - _lastCheck)
                    .count() > 500) {
            _lastCheck = std::chrono::high_resolution_clock::now();
            checkEntitiesInClients();
        }
        std::vector <std::string> protocol = _core->mainLoop(_events);
        if (_core->isReset()) {
            _core->setReset(false);
            Event evt;
            evt.ACTION_NAME = ACTION::RESET;
            evt.body = "";
            _udpServer->sendEventToAllClients(evt);
        }
        for (auto message: protocol) {
            if (message.substr(0, message.find(" ")) == "esound") {
                Event evt;
                evt.ACTION_NAME = ACTION::SOUND;
                evt.body = message;
                _udpServer->sendEventToAllClients(evt);
            } else if (message.substr(0, message.find(" ")) == "etext") {
                Event evt;
                evt.ACTION_NAME = ACTION::TEXT;
                evt.body = message;
                _udpServer->sendEventToAllClients(evt);
            } else if (message.substr(0, message.find(" ")) == "eflip") {
                Event evt;
                evt.ACTION_NAME = ACTION::FLIP;
                evt.body = message;
                _udpServer->sendEventToAllClients(evt);
            } else {
                Event evt;
                evt.ACTION_NAME = ACTION::SPRITE;
                evt.body = message;
                _udpServer->sendEventToAllClients(evt);
            }
        }
    }
}

void Instance::checkEntitiesInClients() {
    int entitiesNb = 0;
    for (auto entityType: _core->getEngine()->getEntities()) {
        for (auto entity: entityType->getEntities()) {
            entitiesNb++;
        }
    }
    _udpServer->sendEventToAllClients({ACTION::CHECK, std::to_string(entitiesNb)});
}