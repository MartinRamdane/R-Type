/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Game.hpp
*/

#pragma once
#include <map>
#include <sstream>
#include "Entity.hpp"
#include "RessourceManager.hpp"
#include "Parser.hpp"
#include "JsonParser.hpp"
#include "TCPClient.hpp"
#include "EventHandler.hpp"
#include <thread>
#include <queue>

class Game
{
public:
    Game();
    ~Game(){};
    void run();
    void animate();
    void draw();
    void handleEvent();
    void update();
    void getinfos(){};
    void connectToServer(std::string host, int port, boost::asio::io_service &io_service);

public:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    sf::Clock _clock;
    RessourceManager _ressourceManager;
    Parser _parser;
    TCPClient *_client;
    int _event_indicator;
    std::queue<std::vector<uint8_t>> _queue;
};
