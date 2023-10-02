/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.cpp
*/

#include "Game.hpp"

Game::Game() : _threadPool(1)
{
    _window.create(sf::VideoMode(1920, 1080), "R-TYPE");
    _window.setFramerateLimit(60);
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
    _ressourceManager = RessourceManager();
    _parser = Parser();
    _parser.parseMessage("ecreate 1 0 0 background.png 0 1 1 ./config.json Background", _ressourceManager);
    _parser.parseMessage("ecreate 2 100 100 Spaceship3.png 0 1 1 ./config.json Spaceship", _ressourceManager);
    _parser.parseMessage("ecreate 3 300 300 Spaceship2.png 0 1 1 ./config.json Spaceship", _ressourceManager);
    _event_indicator = 0;
}

void Game::run()
{
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

void Game::handleEvent()
{
    while (_window.pollEvent(_event))
    {
        if (_event.type == sf::Event::Closed)
            _window.close();
        if (_event.type == sf::Event::KeyPressed)
        {
            Event evt;
            switch (_event.key.code)
            {
            case sf::Keyboard::Left:
                // send left;
                break;
            case sf::Keyboard::Right:
                // send right
                _event_indicator = 0;
                break;
            case sf::Keyboard::Up:
                // send up
                _event_indicator = 1;
                break;
            case sf::Keyboard::Down:
                // send down
                _event_indicator = 2;
                break;
            case sf::Keyboard::Space:
                // send space
                break;
            case sf::Keyboard::Escape:
                _window.close();
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
    _udpClient->connect_to(host, port);
    isUDPClientConnected = true;
    _threadPool.enqueue([this] {
        while (true)
        {
            std::string data = _udpClient->receive_data();
            std::cout << "data: " << data << std::endl;
        }
    });
    return true;
}