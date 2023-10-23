/*
** EPITECH PROJECT, 2023
** Instance.cpp
** File description:
** Instance
*/

#include "Instance.hpp"

Instance::Instance(int id, std::string gameName)
    : _id(id), _port((int)(4210 + id)), _threadPool(3), _gameName(gameName) {
    std::string gameConfigFilePathName = gameName + "InstanceConfig.json";
    nlohmann::json jsonFile = _jsonParser.readFile(gameConfigFilePathName);
    _nbPlayersMax = _jsonParser.get<int>(jsonFile, "nbPlayersMax");
    _onlyMultiplayer = _jsonParser.get<bool>(jsonFile, "onlyMultiplayer");
    std::cout << "nbplayersmax: " << _nbPlayersMax << " only multiplayer "
              << _onlyMultiplayer << std::endl;
    _udpServer = new UDPServer(_io_service, (int)(4210 + id));
    _udpServer->setNbPlayers(1);
    _core = new Core();
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
            continue;  // TODO: destroy the instance
        }
        std::vector<std::string> protocol = _core->mainLoop(_events);
        if (_core->isReset()) {
            _core->setReset(false);
            Event evt;
            evt.ACTION_NAME = ACTION::RESET;
            evt.body_size = 0;
            evt.body = "";
            _udpServer->sendEventToAllClients(evt);
        }
        for (auto message : protocol) {
            if (message.substr(0, message.find(" ")) == "eflip") {
                Event evt;
                evt.ACTION_NAME = ACTION::FLIP;
                evt.body_size = message.size();
                evt.body = message;
                _udpServer->sendEventToAllClients(evt);
            } else {
                Event evt;
                evt.ACTION_NAME = ACTION::SPRITE;
                evt.body_size = message.size();
                evt.body = message;
                _udpServer->sendEventToAllClients(evt);
            }
        }
    }
}
