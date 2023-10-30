/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** InstanceMenu.cpp
*/

#include "InstanceMenu.hpp"
#include "TCPClientImpl.hpp"

InstanceMenu::InstanceMenu(Game *game) : _game(game) {
    _window.create(sf::VideoMode(1920, 1080), "My _window");
    _window.setFramerateLimit(60);
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
    _openInstanceModal = false;
    std::shared_ptr <RessourceManager> ressourceManager = std::make_shared<RessourceManager>();
    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;

    _entities["background"] = std::make_unique<Entity>(ressourceManager);
    _entities["background"]->setTexture("background.png");
    _entities["background"]->setPosition(0, 0);

    _texts["title"] = std::make_unique<sf::Text>();
    _texts["title"]->setFont(_font);
    _texts["title"]->setString("Instances list");
    _texts["title"]->setCharacterSize(20);
    _texts["title"]->setPosition(sf::Vector2f(325, 50));

    _entities["listBackground"] = std::make_unique<Entity>(ressourceManager);
    _entities["listBackground"]->setTexture("listMenu.png");
    _entities["listBackground"]->setPosition(425, 280);
    _entities["listBackground"]->setSpriteScale(1, 1);
    _entities["listBackground"]->setRect(1, 0);
    _entities["listBackground"]->setSpriteOriginToCenter();

    _entities["pCreateInstanceButton"] = std::make_unique<Entity>(ressourceManager);
    _entities["pCreateInstanceButton"]->setTexture("button.png");
    _entities["pCreateInstanceButton"]->setRect(1, 0);
    _entities["pCreateInstanceButton"]->setPosition(220, 100);
    _entities["pCreateInstanceButton"]->setSpriteScale(1.5, 1.5);

    _texts["pCreateInstanceText"] = std::make_unique<sf::Text>();
    _texts["pCreateInstanceText"]->setFont(_font);
    _texts["pCreateInstanceText"]->setString("Create Instance");
    _texts["pCreateInstanceText"]->setCharacterSize(12);
    _texts["pCreateInstanceText"]->setPosition(sf::Vector2f(230, 108));

    _entities["pRefreshList"] = std::make_unique<Entity>(ressourceManager);
    _entities["pRefreshList"]->setTexture("refreshButton.png");
    _entities["pRefreshList"]->setRect(1, 0);
    _entities["pRefreshList"]->setPosition(380, 100);
    _entities["pRefreshList"]->setSpriteScale(1.5, 1.5);

    _entities["modalBackground"] = std::make_unique<Entity>(ressourceManager);
    _entities["modalBackground"]->setTexture("listMenu.png");
    _entities["modalBackground"]->setRect(1, 0);
    _entities["modalBackground"]->setPosition(425, 280);
    _entities["modalBackground"]->setSpriteScale(1, 1);
    _entities["modalBackground"]->setSpriteOriginToCenter();

    _texts["modalTitle"] = std::make_unique<sf::Text>();
    _texts["modalTitle"]->setFont(_font);
    _texts["modalTitle"]->setString("Create Instance");
    _texts["modalTitle"]->setCharacterSize(20);
    _texts["modalTitle"]->setPosition(sf::Vector2f(325, 100));

    _entities["modalExitButton"] = std::make_unique<Entity>(ressourceManager);
    _entities["modalExitButton"]->setTexture("button.png");
    _entities["modalExitButton"]->setRect(1, 0);
    _entities["modalExitButton"]->setPosition(355, 400);
    _entities["modalExitButton"]->setSpriteScale(1.5, 1.5);

    _texts["modalExitButtonText"] = std::make_unique<sf::Text>();
    _texts["modalExitButtonText"]->setFont(_font);
    _texts["modalExitButtonText"]->setString("Cancel");
    _texts["modalExitButtonText"]->setCharacterSize(16);
    _texts["modalExitButtonText"]->setPosition(sf::Vector2f(394, 405));

    // TODO: create dynamically game selector for each games we support

    _gameSelector["rType"] = std::make_unique<Entity>(ressourceManager);
    _gameSelector["rType"]->setTexture("gameSelectorRtype.png");
    _gameSelector["rType"]->setRect(1, 0);
    _gameSelector["rType"]->setPosition(220, 150);
    _gameSelector["rType"]->setSpriteScale(1, 1);

    _gameSelector["pong"] = std::make_unique<Entity>(ressourceManager);
    _gameSelector["pong"]->setTexture("gameSelectorPong.png");
    _gameSelector["pong"]->setRect(1, 0);
    _gameSelector["pong"]->setPosition(430, 150);
    _gameSelector["pong"]->setSpriteScale(1, 1);

    // gap between each instance button is 90 pixels in y
}

InstanceMenu::~InstanceMenu() {
    _window.close();
}

void InstanceMenu::mainloop() {
    _client = _game->getClient();
    while (_window.isOpen()) {
        sf::Event event;
        if (!_client->Incoming().empty()) {
            auto msg = _client->Incoming().pop_front().msg;
            _client->HandleMessage(msg);
        }
        while (_window.pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            sf::Vector2f worldMousePosition = _window.mapPixelToCoords(mousePosition);

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                for (auto &instanceButton: _instanceButtons) {
                    std::string key =
                            "submitButton" + std::to_string(instanceButton.second.get()->getId());
                    Entity *submitButton = instanceButton.second.get()->getSubmitButton();
                    if (submitButton->getSprite().getGlobalBounds().contains(worldMousePosition)) {
                        int port = instanceButton.second.get()->getPort();
                        _game->connectToUdpServer(_game->getHost(), port);
                        return;
                    }
                }
                if (_entities["pRefreshList"]->getSprite().getGlobalBounds().contains(
                        worldMousePosition)) {
                    std::cout << "refresh list" << std::endl;
                    _client->SendEvent({ACTION::LIST, ""});
                }

                if (_entities["pCreateInstanceButton"]->getSprite().getGlobalBounds().contains(
                        worldMousePosition)) {
                    _openInstanceModal = true;
                }

                if (_openInstanceModal &&
                    _entities["modalExitButton"]->getSprite().getGlobalBounds().contains(
                            worldMousePosition)) {
                    _openInstanceModal = false;
                }
                if (_openInstanceModal) {
                    for (auto &gameSelector: _gameSelector) {
                        if (gameSelector.second->getSprite().getGlobalBounds().contains(
                                worldMousePosition)) {
                            std::cout << "select game " << gameSelector.first << std::endl;
                            Event evt;
                            evt.ACTION_NAME = ACTION::CREATE;
                            std::string body = gameSelector.first;
                            evt.body = body;
                            _game.get()->getClient()->SendEvent(evt);
                            return;
                        }
                    }
                }
            }
        }

        _window.clear();
        _window.setView(_view);
        _window.draw(_entities["background"]->getSprite());
        int y = 170;
        for (auto &instanceButton: _instanceButtons) {
            instanceButton.second->setPosition(225, y);
            y += 90;
        }
        if (!_openInstanceModal) {
            _window.draw(_entities["listBackground"]->getSprite());
            _window.draw(_entities["pCreateInstanceButton"]->getSprite());
            _window.draw(_entities["pRefreshList"]->getSprite());
            _window.draw(*_texts["pCreateInstanceText"]);
            _window.draw(*_texts["title"]);
            for (auto &instanceButton: _instanceButtons) {
                for (auto &entity: instanceButton.second->getEntities()) {
                    _window.draw(entity.second->getSprite());
                }
                for (auto &text: instanceButton.second->getTexts())
                    _window.draw(*text.second);
            }
        }
        if (_openInstanceModal) {
            _window.draw(_entities["modalBackground"]->getSprite());
            _window.draw(*_texts["modalTitle"]);
            _window.draw(_entities["modalExitButton"]->getSprite());
            _window.draw(*_texts["modalExitButtonText"]);
            for (auto &gameSelector: _gameSelector) {
                _window.draw(gameSelector.second->getSprite());
            }
        }
        if (!_errorConnect)
            _window.draw(*_texts["ErrorConnexion"]);
        _window.display();
    }
}

void InstanceMenu::addInstanceButton(InstanceType instance, int x, int y) {
    std::cout << "add instance button" << std::endl;
    _instanceButtons[instance.id] = std::make_unique<InstanceButton>(instance, x, y);
}