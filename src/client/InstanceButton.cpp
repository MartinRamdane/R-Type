/*
** EPITECH PROJECT, 2023
** InstanceButton.cpp
** File description:
** InstanceButton
*/
#include "InstanceButton.hpp"

InstanceButton::InstanceButton(InstanceType instance, int x, int y) {

    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;
    std::shared_ptr <RessourceManager> ressourceManager = std::make_shared<RessourceManager>();
    _instance = instance;
    _x = x;
    _y = y;
    _entities[formatText("instanceBackground")] = std::make_shared<Entity>(ressourceManager);
    _entities[formatText("instanceBackground")]->setTexture(
            "instanceBackground.png");
    _entities[formatText("instanceBackground")]->setPosition(_x, _y);
    _entities[formatText("instanceBackground")]->setRect(1, 0);
    _entities[formatText("instanceBackground")]->setSpriteScale(1, 1);

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

    _entities[formatText("userIcon")] = std::make_shared<Entity>(ressourceManager);
    _entities[formatText("userIcon")]->setTexture("userIcon.png");
    _entities[formatText("userIcon")]->setPosition(_x + 10, _y + 55);
    _entities[formatText("userIcon")]->setSpriteScale(1.5, 1.5);
    _entities[formatText("userIcon")]->setRect(1, 0);

    std::string playersText =
            std::to_string(_instance.nbPlayers) + " / " + std::to_string(_instance.maxPlayers);
    _texts[formatText("playersText")] = std::make_shared<sf::Text>();
    _texts[formatText("playersText")]->setFont(_font);
    _texts[formatText("playersText")]->setString(playersText);
    _texts[formatText("playersText")]->setCharacterSize(16);
    _texts[formatText("playersText")]->setFillColor(sf::Color::White);
    _texts[formatText("playersText")]->setPosition(sf::Vector2f(_x + 30, _y + 55));
    std::cout << "nb players of instance: " << instance.nbPlayers << std::endl;
    std::cout << "max players of instance: " << instance.maxPlayers << std::endl;
    if (instance.nbPlayers < instance.maxPlayers) {
        _entities[formatText("submitButton")] = std::make_shared<Entity>(ressourceManager);
        _entities[formatText("submitButton")]->setTexture("button.png");
        _entities[formatText("submitButton")]->setPosition(_x + 250, _y + 50);
        _entities[formatText("submitButton")]->setSpriteScale(1.5, 1.5);

        _texts[formatText("submitButtonText")] = std::make_shared<sf::Text>();
        _texts[formatText("submitButtonText")]->setFont(_font);
        _texts[formatText("submitButtonText")]->setString("Join game");
        _texts[formatText("submitButtonText")]->setCharacterSize(16);
        _texts[formatText("submitButtonText")]->setFillColor(sf::Color::White);
        _texts[formatText("submitButtonText")]->setPosition(sf::Vector2f(_x + 275, _y + 55));
    }
}

InstanceButton::~InstanceButton() {}

std::string InstanceButton::formatText(std::string toFormat) {
    return toFormat + std::to_string(_instance.id);
}

Entity *InstanceButton::getSubmitButton() {
    return _entities[formatText("submitButton")].get();
}

void InstanceButton::setPosition(int x, int y) {
    _x = x;
    _y = y;
    _entities[formatText("instanceBackground")]->setPosition(_x, _y);
    _texts[formatText("instanceName")]->setPosition(sf::Vector2f(_x + 10, _y));
    _texts[formatText("instanceGame")]->setPosition(sf::Vector2f(_x + 10, _y + 25));
    _entities[formatText("userIcon")]->setPosition(_x + 10, _y + 55);
    _texts[formatText("playersText")]->setPosition(sf::Vector2f(_x + 30, _y + 55));
    if (hasSubmitButton()) {
        _entities[formatText("submitButton")]->setPosition(_x + 250, _y + 50);
        _texts[formatText("submitButtonText")]->setPosition(sf::Vector2f(_x + 275, _y + 55));
    }
}