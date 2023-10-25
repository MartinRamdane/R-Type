/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "TCPClientImpl.hpp"
#include "SFML/DisplaySFML.hpp"

Game::Game() : _threadPool(2)
{
    _event_indicator = 0;
    _gameTitle = "game";
    _width = 850;
    _height = 478;
    _playerId = 0;
    closed = false;
    _progressBar = ProgressBar();
}

void Game::setLibToUse()
{
    // if (_lib == Lib::SDL) {
    //     _display = std::make_shared<DisplaySDL>();
    // }
    // else
    if (_lib == Lib::SFML) {
        _display = std::make_shared<DisplaySFML>();
    }
}

void Game::run()
{
    setLib(1);
    setLibToUse();
    while (_display->getClosed() == false)
    {
        if (_client->Incoming().empty() == false)
        {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        if (isUDPClientConnected == true)
        {
            _display->createWindow(_gameTitle, _width, _height);
            Event evt;
            evt.ACTION_NAME = ACTION::READY;
            evt.body = "";
            _udpClient->sendEvent(evt);
            _threadPool.enqueue([this]
                                { this->LoopUDPMessages(); });
            while (_display->windowIsOpen() == true)
            {
                if (_client->Incoming().empty() == false)
                {
                    auto msg = _client->Incoming().pop_front().msg;
                    _client->HandleMessage(msg);
                }
                _display->handleEvent(_udpClient, _client);
                _display->update(&_entities, _udpClient);
            }
        }
    }
    exit(0);
}

void Game::LoopUDPMessages()
{
    while (1)
    {
        if (_udpClient->Incoming().empty() == false)
        {
            auto msg = _udpClient->Incoming().pop_front();
            _udpClient->HandleMessage(msg);
        }
    }
}

void Game::setPlayerId(int id)
{
    _playerId = id;
    _display->setPlayerId(id);
}

bool Game::connectToServer(std::string host, int port)
{
    _client = new TCPClientImpl();
    _client->setGame(this);
    bool connected = _client->Connect(host, port, this);
    _host = host;
    return connected;
}

bool Game::connectToUdpServer(std::string host, int port)
{
    _udpClient = new UDPClient();
    _udpClient->setGameRef(this);
    _udpClient->connect_to(host, port);
    isUDPClientConnected = true;
    return true;
}

bool Game::findEntity(int id)
{
    std::map<int, std::shared_ptr<IEntity>>::iterator it = _entities.begin();
    while (it != _entities.end())
    {
        if (it->first == id)
            return true;
        it++;
    }
    return false;
}

void Game::removeEntity(int id)
{
    _entities.erase(id * -1);
}

void Game::addEntity(IEntity::EntityInfos entityInfos)
{
    if (findEntity(entityInfos.id) == true)
    {
        // if (entity.getHit() == true && id == _playerId)
        // {
        //     float percent = _progressBar.getProgress();
        //     _progressBar.setProgress(percent - 10);
        // }
        // else
        _entities[entityInfos.id]->setNextPos(entityInfos.nextX, entityInfos.nextY);
    }
    else
        _entities[entityInfos.id] = _display->createEntity(entityInfos);
}

void Game::flipEntity(int id)
{
    _entities[id]->flip();
}

void Game::setLib(int lib)
{
    if (lib == 1)
        _lib = SFML;
    else if (lib == 2)
        _lib = SDL;
}