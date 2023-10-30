/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "SFML/DisplaySFML.hpp"
#include "TCPClientImpl.hpp"

Game::Game() : _threadPool(2) {
    _event_indicator = 0;
    _gameTitle = "game";
    _width = 850;
    _height = 478;
    _playerId = 0;
    closed = false;
    _progressBar = ProgressBar();
}

Game::~Game() {
    _entities.clear();
    _entitiesToRemove.clear();
}

void Game::setLibToUse() {
    // if (_lib == Lib::SDL) {
    //     _display = std::make_unique<DisplaySDL>();
    // }
    // else
    if (_lib == Lib::SFML) {
        _display = std::make_unique<DisplaySFML>();
    }
}

void Game::run() {
    setLib(1);
    setLibToUse();
    while (_display->getClosed() == false) {
        if (_client->Incoming().empty() == false) {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        if (isUDPClientConnected == true) {
            _display->createWindow(_gameTitle, _width, _height);
            Event evt;
            evt.ACTION_NAME = ACTION::READY;
            evt.body = "";
            _udpClient->sendEvent(evt);
            _threadPool.enqueue([this] { this->LoopUDPMessages(); });
            _threadPool.enqueue([this] { this->loopEventQueue(); });
            while (_display->windowIsOpen() == true) {
                _display->handleEvent(_udpClient, _client);
                if (_entitiesToRemove.empty() == false) {
                    std::lock_guard<std::mutex> lock(entityMutex);
                    {
                        for (auto it = _entitiesToRemove.begin(); it != _entitiesToRemove.end();
                             it++) {
                            _entities.erase((*it) * -1);
                        }
                        _entitiesToRemove.clear();
                    }
                }
                std::map<int, std::shared_ptr<IEntity>> entitiesCopy;
                {
                    std::lock_guard<std::mutex> lock(entityMutex);
                    entitiesCopy = _entities;
                }
                _display->update(&entitiesCopy, _udpClient);
            }
        }
    }
}

void Game::LoopUDPMessages() {
    while (1) {
        if (_udpClient->Incoming().empty() == false) {
            auto msg = _udpClient->Incoming().pop_front();
            _udpClient->HandleMessage(msg);
        }
    }
}

void Game::loopEventQueue() {
    while (1) {
        _udpClient->sendUnknownEntities();
        if (_udpClient->getEventQueue().empty() == false) {
            auto evt = _udpClient->getEventQueue().pop_front();
            handleReceivedEvent(evt);
        }
    }
}

void Game::setPlayerId(int id) {
    _playerId = id;
    _display->setPlayerId(id);
}

bool Game::connectToServer(std::string host, int port) {
    _client = std::make_shared<TCPClientImpl>();
    _client->setGame(this);
    bool connected = _client->Connect(host, port, this);
    _host = host;
    return connected;
}

bool Game::connectToUdpServer(std::string host, int port) {
    _udpClient = std::make_shared<UDPClient>();
    _udpClient->connect_to(host, port);
    isUDPClientConnected = true;
    return true;
}

bool Game::findEntity(int id) {
    std::map<int, std::shared_ptr<IEntity>>::iterator it = _entities.begin();
    while (it != _entities.end()) {
        if (it->first == id)
            return true;
        it++;
    }
    _udpClient->addUnknownEntity(id);
    return false;
}

void Game::removeEntity(int id) {
    _entitiesToRemove.push_back(id);
}

void Game::addEntity(IEntity::EntityInfos entityInfos) {
    if (findEntity(entityInfos.id) == true) {
        // if (entity.getHit() == true && id == _playerId)
        // {
        //     float percent = _progressBar.getProgress();
        //     _progressBar.setProgress(percent - 10);
        // }
        // else
        _entities.at(entityInfos.id)->setNextPos(entityInfos.nextX, entityInfos.nextY);
        if (entityInfos.type == IEntity::Type::TEXT)
            _entities.at(entityInfos.id)->setTextString(entityInfos.text);
    } else {
        std::cout << "going here " << std::endl;
        auto entity = _display->createEntity(entityInfos);
        if (entity != nullptr) {
            _entities.insert(std::pair<int, std::shared_ptr<IEntity>>(
                entityInfos.id, _display->createEntity(entityInfos)));
        }
    }
}

void Game::flipEntity(Event evt) {
    std::stringstream ss(evt.body);
    std::string tpm;
    std::string id;
    ss >> tpm;
    ss >> id;
    int entityId = std::stoi(id);
    _entities[entityId]->flip();
}

void Game::updateSprite(Event evt) {
    IEntity::EntityInfos entityInfos = parseRef.parseMessage(evt);
    std::cout << "entity path : " << entityInfos.path << std::endl;
    std::cout << "entity id : " << entityInfos.id << std::endl;
    if (entityInfos.id < 0)
        removeEntity(entityInfos.id);
    else
        addEntity(entityInfos);
}

void Game::updateText(Event evt) {
    std::stringstream ss(evt.body);
    std::string id;
    std::string x;
    std::string y;
    std::string text;
    std::string color;
    std::string objectType;
    ss >> id;
    ss >> x;
    ss >> y;
    ss >> text;
    ss >> color;
    ss >> objectType;
    Parser parseRef;
    IEntity::EntityInfos entityInfos = parseRef.parseMessage(evt);
    if (entityInfos.id < 0)
        removeEntity(entityInfos.id);
    else
        addEntity(entityInfos);
}

void Game::joinGame(Event evt) {
    std::stringstream ss(evt.body);
    std::string gameTitle;
    std::string width;
    std::string height;
    ss >> gameTitle;
    ss >> width;
    ss >> height;
    isUDPClientConnected = true;
    _gameTitle = gameTitle;
    _width = std::stoi(width);
    _height = std::stoi(height);
}

void Game::setLib(int lib) {
    if (lib == 1)
        _lib = SFML;
    else if (lib == 2)
        _lib = SDL;
}

void Game::handleReceivedEvent(Event evt) {
    switch (evt.ACTION_NAME) {
        case ACTION::PING:
            _udpClient->sendEvent({ACTION::PONG, ""});
            break;
        case ACTION::JOINED:
            joinGame(evt);
            break;
        case ACTION::SPRITE: {
            std::lock_guard<std::mutex> lock(entityMutex);
            updateSprite(evt);
            break;
        }
        case ACTION::TEXT: {
            std::lock_guard<std::mutex> lock(entityMutex);
            updateText(evt);
            break;
        }
        case ACTION::FLIP: {
            std::lock_guard<std::mutex> lock(entityMutex);
            flipEntity(evt);
            break;
        }
        case ACTION::RESET: {
            std::lock_guard<std::mutex> lock(entityMutex);
            _entities.clear();
            break;
        }
        default:
            break;
    }
}