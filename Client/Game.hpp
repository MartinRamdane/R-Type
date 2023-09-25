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

class Game
{
public:
    Game();
    ~Game();
    void run();
    void handleEvent();
    void update();
    void getinfos(){};

public:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    sf::Clock _clock;
    
    RessourceManager _ressourceManager;
    Parser _parser;
};
