/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** startGame.cpp
*/

#include "Menu.hpp"

Menu::Menu(std::shared_ptr<Game>& game) : _game(game) {
    _window.create(sf::VideoMode(1920, 1080), "Table Ronde Games");
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
    _window.setFramerateLimit(60);
    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;

    _entities["background"] = std::make_unique<Entity>();
    _entities["background"]->setNbRect(1);
    _entities["background"]->_texture = std::make_shared<sf::Texture>();
    _entities["background"]->setTexture("assets/cenario/background.png");
    _entities["background"]->setSprite();
    _entities["background"]->setSpritePosition(sf::Vector2f(0, 0));

    _entities["logo"] = std::make_unique<Entity>();
    _entities["logo"]->setNbRect(1);
    _entities["logo"]->_texture = std::make_shared<sf::Texture>();
    _entities["logo"]->setTexture("assets/cenario/Logo.png");
    _entities["logo"]->setSprite();
    _entities["logo"]->setSpritePosition(sf::Vector2f(425, 100));
    _entities["logo"]->setSpriteOrigin();

    _entities["connectButton"] = std::make_unique<Entity>();
    _entities["connectButton"]->setNbRect(1);
    _entities["connectButton"]->_texture = std::make_shared<sf::Texture>();
    _entities["connectButton"]->setTexture("assets/cenario/button.png");
    _entities["connectButton"]->setSprite();
    _entities["connectButton"]->setSpritePosition(sf::Vector2f(425, 380));
    _entities["connectButton"]->setSpriteScale(sf::Vector2f(2.5, 2.5));
    _entities["connectButton"]->setSpriteOrigin();

    _inputs["nameInput"] = std::make_unique<Input>("assets/cenario/TextInput.png",
                                                   "assets/cenario/TextInputHover.png", "Name");
    _inputs["nameInput"]->setSpritePosition(sf::Vector2f(300, 170));
    _inputs["nameInput"]->setSpriteScale(sf::Vector2f(2.5, 2.5));

    _inputs["portInput"] = std::make_unique<Input>("assets/cenario/TextInput.png",
                                                   "assets/cenario/TextInputHover.png", "Port");
    _inputs["portInput"]->setSpritePosition(sf::Vector2f(300, 230));
    _inputs["portInput"]->setSpriteScale(sf::Vector2f(2.5, 2.5));

    _inputs["ipInput"] = std::make_unique<Input>("assets/cenario/TextInput.png",
                                                 "assets/cenario/TextInputHover.png", "IP Adress");
    _inputs["ipInput"]->setSpritePosition(sf::Vector2f(300, 290));
    _inputs["ipInput"]->setSpriteScale(sf::Vector2f(2.5, 2.5));

    _texts["connect"] = std::make_unique<sf::Text>();
    _texts["connect"]->setFont(_font);
    _texts["connect"]->setString("connect");
    _texts["connect"]->setCharacterSize(20);
    _texts["connect"]->setFillColor(sf::Color::White);
    _texts["connect"]->setPosition(sf::Vector2f(425, 380));
    _texts["connect"]->setOrigin(sf::Vector2f(_texts["connect"]->getLocalBounds().width / 2,
                                              _texts["connect"]->getLocalBounds().height / 2));

    _texts["ErrorConnexion"] = std::make_unique<sf::Text>();
    _texts["ErrorConnexion"]->setFont(_font);
    _texts["ErrorConnexion"]->setString("Error: Could not connect to server");
    _texts["ErrorConnexion"]->setCharacterSize(20);
    _texts["ErrorConnexion"]->setFillColor(sf::Color::Red);
    _texts["ErrorConnexion"]->setPosition(sf::Vector2f(425, 425));
    _texts["ErrorConnexion"]->setOrigin(
        sf::Vector2f(_texts["ErrorConnexion"]->getLocalBounds().width / 2,
                     _texts["ErrorConnexion"]->getLocalBounds().height / 2));
}

Menu::~Menu() {
    _window.close();
}

void Menu::mainloop() {
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            for (auto& input : _inputs) {
                input.second->eventHandler(event, _window);
            }
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            sf::Vector2f worldMousePosition = _window.mapPixelToCoords(mousePosition);

            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                if (_entities["connectButton"]->getSprite().getGlobalBounds().contains(
                        worldMousePosition)) {
                    _login.name = _inputs["nameInput"]->getText();
                    _login.port = _inputs["portInput"]->getText();
                    _login.ip = _inputs["ipInput"]->getText();
                    if ((_errorConnect =
                             _game->connectToServer(_login.ip, std::atoi(_login.port.c_str())))) {
                        return;
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return &&
                _inputs["ipInput"]->getActive()) {
                {
                    if (_inputs["nameInput"]->getText() != "" &&
                        _inputs["portInput"]->getText() != "" &&
                        _inputs["ipInput"]->getText() != "") {
                        _login.name = _inputs["nameInput"]->getText();
                        _login.port = _inputs["portInput"]->getText();
                        _login.ip = _inputs["ipInput"]->getText();
                        if ((_errorConnect = _game->connectToServer(
                                 _login.ip, std::atoi(_login.port.c_str())))) {
                            return;
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed &&
                (event.key.code == sf::Keyboard::Tab || event.key.code == sf::Keyboard::Return)) {
                if (_inputs["nameInput"]->getActive()) {
                    _inputs["nameInput"]->setActive(false);
                    _inputs["portInput"]->setActive(true);
                } else if (_inputs["portInput"]->getActive()) {
                    _inputs["portInput"]->setActive(false);
                    _inputs["ipInput"]->setActive(true);
                } else if (_inputs["ipInput"]->getActive()) {
                    _inputs["ipInput"]->setActive(false);
                    _inputs["nameInput"]->setActive(true);
                }
            }
        }
        for (auto& input : _inputs) {
            input.second->update();
        }

        _window.clear();
        _window.setView(_view);
        _window.draw(_entities["background"]->getSprite());
        _window.draw(_entities["logo"]->getSprite());
        for (auto& input : _inputs) {
            input.second->draw(_window);
        }
        _window.draw(_entities["connectButton"]->getSprite());
        _window.draw(*_texts["connect"]);
        if (!_errorConnect)
            _window.draw(*_texts["ErrorConnexion"]);

        _window.display();
    }
}
