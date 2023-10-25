/*
** EPITECH PROJECT, 2023
** InstanceButton.cpp
** File description:
** InstanceButton
*/
#include "InstanceButton.hpp"

InstanceButton::InstanceButton(Instance instance, int instanceId, int x, int y) {
    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;
    _instance = instance;
    _instanceId = instanceId;
    _x = x;
    _y = y;
    _entities[formatText("instanceBackground")] = std::make_shared<Entity>();
    _entities[formatText("instanceBackground")]->setNbRect(1);
    _entities[formatText("instanceBackground")]->_texture = std::make_shared<sf::Texture>();
    _entities[formatText("instanceBackground")]->setTexture(
        "assets/cenario/instanceBackground.png");
    _entities[formatText("instanceBackground")]->setSprite();
    _entities[formatText("instanceBackground")]->setSpritePosition(sf::Vector2f(_x, _y));
    _entities[formatText("instanceBackground")]->setSpriteScale(sf::Vector2f(1, 1));

    _texts[formatText("instanceName")] = std::make_shared<sf::Text>();
    _texts[formatText("instanceName")]->setFont(_font);
    _texts[formatText("instanceName")]->setString(_instance.name);
    _texts[formatText("instanceName")]->setCharacterSize(20);
    _texts[formatText("instanceName")]->setFillColor(sf::Color::White);
    _texts[formatText("instanceName")]->setPosition(sf::Vector2f(_x + 10, _y));

    _texts[formatText("instanceGame")] = std::make_shared<sf::Text>();
    _texts[formatText("instanceGame")]->setFont(_font);
    _texts[formatText("instanceGame")]->setString(_instance.game);
    _texts[formatText("instanceGame")]->setCharacterSize(16);
    _texts[formatText("instanceGame")]->setFillColor(sf::Color::White);
    _texts[formatText("instanceGame")]->setPosition(sf::Vector2f(_x + 10, _y + 25));

    _entities[formatText("userIcon")] = std::make_shared<Entity>();
    _entities[formatText("userIcon")]->setNbRect(1);
    _entities[formatText("userIcon")]->_texture = std::make_shared<sf::Texture>();
    _entities[formatText("userIcon")]->setTexture("assets/cenario/userIcon.png");
    _entities[formatText("userIcon")]->setSprite();
    _entities[formatText("userIcon")]->setSpritePosition(sf::Vector2f(_x + 10, _y + 55));
    _entities[formatText("userIcon")]->setSpriteScale(sf::Vector2f(1.5, 1.5));

    std::string playersText =
        std::to_string(_instance.nbPlayers) + " / " + std::to_string(_instance.maxPlayers);
    _texts[formatText("playersText")] = std::make_shared<sf::Text>();
    _texts[formatText("playersText")]->setFont(_font);
    _texts[formatText("playersText")]->setString(playersText);
    _texts[formatText("playersText")]->setCharacterSize(16);
    _texts[formatText("playersText")]->setFillColor(sf::Color::White);
    _texts[formatText("playersText")]->setPosition(sf::Vector2f(_x + 30, _y + 55));

    _entities[formatText("submitButton")] = std::make_shared<Entity>();
    _entities[formatText("submitButton")]->setNbRect(1);
    _entities[formatText("submitButton")]->_texture = std::make_shared<sf::Texture>();
    _entities[formatText("submitButton")]->setTexture("assets/cenario/button.png");
    _entities[formatText("submitButton")]->setSprite();
    _entities[formatText("submitButton")]->setSpritePosition(sf::Vector2f(_x + 250, _y + 50));
    _entities[formatText("submitButton")]->setSpriteScale(sf::Vector2f(1.5, 1.5));

    _texts[formatText("submitButtonText")] = std::make_shared<sf::Text>();
    _texts[formatText("submitButtonText")]->setFont(_font);
    _texts[formatText("submitButtonText")]->setString("Join game");
    _texts[formatText("submitButtonText")]->setCharacterSize(16);
    _texts[formatText("submitButtonText")]->setFillColor(sf::Color::White);
    _texts[formatText("submitButtonText")]->setPosition(sf::Vector2f(_x + 275, _y + 55));
}

InstanceButton::~InstanceButton() {}

std::string InstanceButton::formatText(std::string toFormat) {
    return toFormat + std::to_string(_instanceId);
}