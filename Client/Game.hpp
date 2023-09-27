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
#include <thread>

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
    void connectToServer(std::string host, int port);

public:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    sf::Clock _clock;
    RessourceManager _ressourceManager;
    Parser _parser;
    TCPClient *_client;
    int _event_indicator;
};
