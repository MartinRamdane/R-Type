/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** startGame.cpp
*/

#include "Editor.hpp"

Editor::Editor() {
    _window.create(sf::VideoMode(1920, 1080), "My _window");
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
    _window.setFramerateLimit(60);
    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;

    // std::shared_ptr<RessourceManager> ressourceManager = std::make_shared<RessourceManager>();

    // _entities["background"] = std::make_unique<Entity>(ressourceManager);
    // _entities["background"]->setTexture("background.png");
    // _entities["background"]->setPosition(0, 0);

    // _entities["logo"] = std::make_unique<Entity>(ressourceManager);
    // _entities["logo"]->setTexture("Logo.png");
    // _entities["logo"]->setPosition(425, 100);
    // _entities["logo"]->setRect(1, 0);
    // _entities["logo"]->setSpriteOriginToCenter();

    // _entities["connectButton"] = std::make_unique<Entity>(ressourceManager);
    // _entities["connectButton"]->setTexture("button.png");
    // _entities["connectButton"]->setPosition(425, 380);
    // _entities["connectButton"]->setSpriteScale(2.5, 2.5);
    // _entities["connectButton"]->setRect(1, 0);
    // _entities["connectButton"]->setSpriteOriginToCenter();

    // _inputs["nameInput"] = std::make_unique<Input>("assets/cenario/TextInput.png",
    //                                                "assets/cenario/TextInputHover.png", "Name");
    // _inputs["nameInput"]->setSpritePosition(sf::Vector2f(300, 170));
    // _inputs["nameInput"]->setSpriteScale(sf::Vector2f(2.5, 2.5));

    // _inputs["portInput"] = std::make_unique<Input>("assets/cenario/TextInput.png",
    //                                                "assets/cenario/TextInputHover.png", "Port");
    // _inputs["portInput"]->setSpritePosition(sf::Vector2f(300, 230));
    // _inputs["portInput"]->setSpriteScale(sf::Vector2f(2.5, 2.5));

    // _inputs["ipInput"] = std::make_unique<Input>("assets/cenario/TextInput.png",
    //                                              "assets/cenario/TextInputHover.png", "IP Adress");
    // _inputs["ipInput"]->setSpritePosition(sf::Vector2f(300, 290));
    // _inputs["ipInput"]->setSpriteScale(sf::Vector2f(2.5, 2.5));

    // _texts["connect"] = std::make_unique<sf::Text>();
    // _texts["connect"]->setFont(_font);
    // _texts["connect"]->setString("connect");
    // _texts["connect"]->setCharacterSize(20);
    // _texts["connect"]->setFillColor(sf::Color::White);
    // _texts["connect"]->setPosition(sf::Vector2f(425, 380));
    // _texts["connect"]->setOrigin(sf::Vector2f(_texts["connect"]->getLocalBounds().width / 2,
    //                                           _texts["connect"]->getLocalBounds().height / 2));

    // _texts["ErrorConnexion"] = std::make_unique<sf::Text>();
    // _texts["ErrorConnexion"]->setFont(_font);
    // _texts["ErrorConnexion"]->setString("Error: Could not connect to server");
    // _texts["ErrorConnexion"]->setCharacterSize(20);
    // _texts["ErrorConnexion"]->setFillColor(sf::Color::Red);
    // _texts["ErrorConnexion"]->setPosition(sf::Vector2f(425, 425));
    // _texts["ErrorConnexion"]->setOrigin(
    //     sf::Vector2f(_texts["ErrorConnexion"]->getLocalBounds().width / 2,
    //                  _texts["ErrorConnexion"]->getLocalBounds().height / 2));
}

Editor::~Editor() {
    _window.close();
}

void Editor::mainloop() {
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {}

        _window.clear();
        _window.display();
    }
}
