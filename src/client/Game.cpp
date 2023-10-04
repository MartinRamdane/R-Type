/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"

Game::Game() : _threadPool(1)
{
    _ressourceManager = RessourceManager();
    _parser = Parser();
    _event_indicator = 0;
    _gameTitle = "game";
    _width = 850;
    _height = 478;
    closed = false;
}

void Game::createWindow(std::string name, int x, int y)
{
     _window.create(sf::VideoMode(x, y), name);
    _window.setFramerateLimit(60);
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
}

void Game::run()
{
    while (closed == false)
    {
        if (_client->Incoming().empty() == false)
        {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        if (isUDPClientConnected == true)
        {
            createWindow(_gameTitle, _width, _height);
            while (_window.isOpen())
            {
                if (_client->Incoming().empty() == false)
                {
                    auto msg = _client->Incoming().pop_front().msg;
                    _client->HandleMessage(msg);
                }
                // getinfos -> appel de parseMessage
                handleEvent();
                update();
            }
        }
    }
    exit(0);
}

void Game::handleEvent()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed) {
            _window.close();
            _client->Disconnect();
            closed = true;
        } if (_event.type == sf::Event::KeyPressed)
        {
            Event evt;
            switch (_event.key.code)
            {
            case sf::Keyboard::Left:
                evt.ACTION_NAME = ACTION::LEFT;
                evt.body_size = 0;
                evt.body = "";
                _udpClient->sendEvent(evt, _udpClient->getHost(), _udpClient->getPort());
                break;
            case sf::Keyboard::Right:
                evt.ACTION_NAME = ACTION::RIGHT;
                evt.body_size = 0;
                evt.body = "";
                _udpClient->sendEvent(evt, _udpClient->getHost(), _udpClient->getPort());
                break;
            case sf::Keyboard::Up:
                evt.ACTION_NAME = ACTION::UP;
                evt.body_size = 0;
                evt.body = "";
                _udpClient->sendEvent(evt, _udpClient->getHost(), _udpClient->getPort());
                _event_indicator = 1;
                break;
            case sf::Keyboard::Down:
                evt.ACTION_NAME = ACTION::DOWN;
                evt.body_size = 0;
                evt.body = "";
                _udpClient->sendEvent(evt, _udpClient->getHost(), _udpClient->getPort());
                _event_indicator = 2;
                break;
            case sf::Keyboard::Space:
                evt.ACTION_NAME = ACTION::SHOOT;
                evt.body_size = 0;
                evt.body = "";
                _udpClient->sendEvent(evt, _udpClient->getHost(), _udpClient->getPort());
                break;
            case sf::Keyboard::Escape:
                _window.close();
                _client->Disconnect();
                closed = true;
                break;
            default:
                break;
            }
        }
        else
            _event_indicator = 0;
    }
}

void Game::animate()
{
    std::map<int, Entity>::iterator it = _parser._entities.begin();
    while (it != _parser._entities.end())
    {
        if (it->second._event_form == "loop")
            it->second.animateSprite(0, 100);
        if (it->second._event_form == "event" && _event_indicator != 0)
            it->second.animateSprite(_event_indicator, 100);
        if (it->second._event_form == "once")
            it->second.animateSprite(3, 100);
        if (it->second._event_form == "event" && _event_indicator == 0)
            it->second.setInitPos();
        if (it->second._event_form == "paralaxe")
            it->second.animateSprite(4, 1);
        it++;
    }
}

void Game::draw()
{
    std::map<int, Entity>::iterator it = _parser._entities.begin();
    while (it != _parser._entities.end())
    {
        _window.draw(it->second.getSprite());
        it++;
    }
}

void Game::update()
{
    _window.clear();
    animate();
    draw();
    _window.setView(_view);
    _window.display();
}

bool Game::connectToServer(std::string host, int port)
{
    _client = new TCPClientImpl();
    _client->setGame(this);
    bool connected = _client->Connect(host, port, this);
    std::cout << "connected: " << connected << std::endl;
    if (connected == false)
        exit(84);
    Event evt;
    evt.ACTION_NAME = ACTION::CREATE;
    evt.body_size = 0;
    evt.body = "";
    _client->SendEvent(evt);
    return connected;
}

bool Game::connectToUdpServer(std::string host, int port)
{
    _udpClient = new UDPClient();
    _udpClient->setGameRef(this);
    _udpClient->connect_to(host, port);
    _threadPool.enqueue([this] {
        while (true)
        {
            _udpClient->receive_data();
        }
    });
    return true;
}