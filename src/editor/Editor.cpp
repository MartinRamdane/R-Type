/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** startGame.cpp
*/

#include "Editor.hpp"

Editor::Editor() {
    _window.create(sf::VideoMode(1920, 1080), "R-Type-Editor");
    _mainView = sf::View(sf::FloatRect(0, 0, 850, 478));
    _menuView = sf::View(sf::FloatRect(0, 0, 850, 478));
    _window.setFramerateLimit(60);
    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;

    _ressourceManager = std::make_shared<RessourceManager>();

    _entities["background"] = std::make_unique<Entity>(_ressourceManager);
    _entities["background"]->setTexture("background.png");
    _entities["background"]->setPosition(0, 0);

    //menu entities
    _entitiesSelectMenu["flyer"] = std::make_unique<Entity>(_ressourceManager);
    _entitiesSelectMenu["flyer"]->setTexture("flyer.png");

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

    _texts["connect"] = std::make_unique<sf::Text>();
    _texts["connect"]->setFont(_font);
    _texts["connect"]->setString("connect");
    _texts["connect"]->setCharacterSize(20);
    _texts["connect"]->setFillColor(sf::Color::White);
    _texts["connect"]->setPosition(sf::Vector2f(425, 380));
    _texts["connect"]->setOrigin(sf::Vector2f(_texts["connect"]->getLocalBounds().width / 2,
                                              _texts["connect"]->getLocalBounds().height / 2));

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

void Editor::keyEvent(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Left) {
            _mainView.move(-10, 0);
            _window.setView(_mainView);
        } else if (event.key.code == sf::Keyboard::Right) {
            _mainView.move(10, 0);
            _window.setView(_mainView);
        } else if (event.key.code == sf::Keyboard::Up) {
            _mainView.move(0, -10);
            _window.setView(_mainView);
        } else if (event.key.code == sf::Keyboard::Down) {
            _mainView.move(0, 10);
            _window.setView(_mainView);
        } else if (event.key.code == sf::Keyboard::Num1) {
            _selectedEntity = "flyer";
        } else if (event.key.code == sf::Keyboard::Num2) {
            _selectedEntity = "OrangeRobot";
        } else if (event.key.code == sf::Keyboard::Num3) {
            _selectedEntity = "robot_type_5";
        } else if (event.key.code == sf::Keyboard::Num4) {
            _selectedEntity = "flyer";
        } else if (event.key.code == sf::Keyboard::Num5) {
            _selectedEntity = "flyer";
        }
    }
}

void Editor::mouseEvent(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);

            sf::Vector2f worldPosition = _window.mapPixelToCoords(mousePosition);

            _entities[_selectedEntity + std::to_string(_entityQuantity[_selectedEntity])] =
                std::make_unique<Entity>(_ressourceManager);
            _entities[_selectedEntity + std::to_string(_entityQuantity[_selectedEntity])]
                ->setTexture(_selectedEntity + ".png");
            _entities[_selectedEntity + std::to_string(_entityQuantity[_selectedEntity])]
                ->setPosition(worldPosition.x, worldPosition.y);
            _entityQuantity[_selectedEntity]++;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            std::cout << "Right click" << std::endl;
            // Handle right-click to remove entities
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            sf::Vector2f worldPosition = _window.mapPixelToCoords(mousePosition);

            // Iterate through the entities and check if any should be removed
            for (auto it = _entities.begin(); it != _entities.end();) {
                if (it->first == "background") {
                    ++it;
                    continue;
                }
                if (it->second->getSprite().getGlobalBounds().contains(worldPosition)) {
                    it = _entities.erase(it);    // Remove the entity
                } else {
                    ++it;
                }
            }
        }
    }
}

void Editor::update() {}

void Editor::mainloop() {
    while (_window.isOpen()) {
        sf::Event event;
        _window.setView(_mainView);
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
            keyEvent(event);
            mouseEvent(event);
        }
        update();
        _window.clear();
        for (auto& entity : _entities) {
            _window.draw(entity.second->getSprite());
        }
        _window.setView(_menuView);
        for (auto& text : _texts) {
            _window.draw(*text.second);
        }
        for (auto& entity : _entitiesSelectMenu) {
            _window.draw(entity.second->getSprite());
        }
        _window.draw(_entitiesSelectMenu[_selectedEntity]->getSprite());
        _window.display();
    }
}
