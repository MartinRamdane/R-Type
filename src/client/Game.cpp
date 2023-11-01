/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "SFML/DisplaySFML.hpp"
#include "TCPClientImpl.hpp"
#include "InstanceMenu.hpp"

Game::Game() : _threadPool(3) {
    _event_indicator = 0;
    _gameTitle = "game";
    _width = 850;
    _height = 478;
    _playerId = 0;
    closed = false;
    _progressBar = ProgressBar();
    _instanceMenu = std::make_unique<InstanceMenu>(this);
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

int Game::getEntitiesNumber() {
    std::lock_guard<std::mutex> lock(entityMutex);
    return _entities.size();
}

void Game::run(std::shared_ptr<sf::RenderWindow> window) {
    setLib(1);
    setLibToUse();
    bool sendListEvent = false;
    while (!_display->getClosed()) {
        if (!_client->Incoming().empty()) {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        if (isTCPClientConnected && !isUDPClientConnected) {
            if (!sendListEvent) {
                Event evt = {ACTION::LIST, ""};
                _client->SendEvent(evt);
            }
            _instanceMenu->mainloop(window);
            sendListEvent = true;
        }
        if (isUDPClientConnected) {
            _display->createWindow(_gameTitle, _width, _height);
            Event evt;
            evt.ACTION_NAME = ACTION::READY;
            evt.body = "";
            _udpClient->sendEvent(evt);
            _threadPool.enqueue([this] { this->LoopUDPMessages(); });
            _threadPool.enqueue([this] { this->loopEventQueue(); });
            while (_display->windowIsOpen()) {
                _display->handleEvent();
                std::map<int, std::shared_ptr<IEntity>> entitiesCopy;
                {
                    std::lock_guard<std::mutex> lock(entityMutex);
                    entitiesCopy = _entities;
                }
                update(&entitiesCopy);
                _display->draw(&entitiesCopy);
            }
        }
    }
}

void Game::update(std::map<int, std::shared_ptr<IEntity>>* entitiesCopy) {
    if (_entitiesToRemove.empty() == false) {
        std::lock_guard<std::mutex> lock(entityMutex);
        {
            for (auto it = _entitiesToRemove.begin(); it != _entitiesToRemove.end(); it++) {
                _entities.erase((*it) * -1);
            }
            _entitiesToRemove.clear();
        }
    }
    handleEvent();
    for (auto it = entitiesCopy->begin(); it != entitiesCopy->end(); it++) {
        (*it).second->update();
        if ((*it).second->isDead()) {
            Event evt;
            evt.ACTION_NAME = ACTION::DEAD;
            evt.body = std::to_string((*it).first);
            _udpClient->sendEvent(evt);
            _udpClient->getEventQueue().push_back(evt);
        }
    }
    animate(entitiesCopy);
}

void Game::animate(std::map<int, std::shared_ptr<IEntity>>* entitiesCopy) {
    std::map<int, std::shared_ptr<IEntity>>::iterator it = entitiesCopy->begin();
    while (it != entitiesCopy->end()) {
        if (it->second->getEventForm() == "loop")
            it->second->animateSprite(0, 60);
        if (it->second->getEventForm() == "once")
            it->second->animateSprite(3, 60);
        if (it->second->getEventForm() == "event")
            it->second->setInitPos();
        if (it->second->getEventForm() == "paralaxe")
            it->second->animateSprite(4, 1);
        it++;
    }
}

void Game::handleEvent() {
    std::vector<std::string> events = _display->getEvents();
    std::string playerId = "p" + std::to_string(_playerId);
    for (auto event : events) {
        Event evt;
        std::string body = "";
        if (event == "close")
            _client->Disconnect();
        if (event == "r")
            evt.ACTION_NAME = ACTION::FLIP;
        if (event == "left")
            evt.ACTION_NAME = ACTION::LEFT;
        if (event == "right")
            evt.ACTION_NAME = ACTION::RIGHT;
        if (event == "up")
            evt.ACTION_NAME = ACTION::UP;
        if (event == "down")
            evt.ACTION_NAME = ACTION::DOWN;
        if (event == "space")
            evt.ACTION_NAME = ACTION::SPACE;
        if (event == "s") {
            evt.ACTION_NAME = ACTION::KEY;
            body = "s ";
        }
        if (event == "l") {
            evt.ACTION_NAME = ACTION::KEY;
            body = "l ";
        }
        if (event == "c") {
            evt.ACTION_NAME = ACTION::KEY;
            body = "c ";
        }
        evt.body = body + playerId;
        _udpClient->sendEvent(evt);
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
        if (_udpClient->getEventQueue().empty() == false) {
            auto evt = _udpClient->getEventQueue().pop_front();
            handleReceivedEvent(evt);
        }
    }
}

void Game::setPlayerId(int id) {
    _playerId = id;
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
    if (entityInfos.id < 0)
        removeEntity(entityInfos.id);
    else
        addEntity(entityInfos);
}

void Game::updateText(Event evt) {
    Parser parseRef;
    IEntity::EntityInfos entityInfos = parseRef.parseMessage(evt);
    if (entityInfos.id < 0)
        removeEntity(entityInfos.id);
    else
        addEntity(entityInfos);
}

void Game::updateSound(Event evt) {
    IEntity::EntityInfos entityInfos = parseRef.parseMessage(evt);
    if (findEntity(entityInfos.id))
        return;
    _entities.insert(std::pair<int, std::shared_ptr<IEntity>>(entityInfos.id,
                                                              _display->createEntity(entityInfos)));
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
        case ACTION::CHECK: {
            int entities = std::stoi(evt.body);
            checkEntities(entities);
            break;
        }
        case ACTION::SOUND: {
            std::lock_guard<std::mutex> lock(entityMutex);
            updateSound(evt);
            break;
        }
        default:
            break;
    }
}

void Game::checkEntities(int nb) {
    int currentNb = getEntitiesNumber();
    if (currentNb < nb) {
        _udpClient->sendEvent({ACTION::CHECK, ""});
    }
}