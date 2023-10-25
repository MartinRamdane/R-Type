/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** InstanceMenu.cpp
*/

#include "InstanceMenu.hpp"

InstanceMenu::InstanceMenu(std::shared_ptr<Game>& game) : _game(game) {
    _window.create(sf::VideoMode(1920, 1080), "Table Ronde Games");
    _view = sf::View(sf::FloatRect(0, 0, 850, 478));
    _window.setFramerateLimit(60);
    _openInstanceModal = false;
    if (!_font.loadFromFile(std::string("font/pixel.ttf")))
        std::cerr << "Error: could not load font" << std::endl;

    _entities["background"] = std::make_unique<Entity>();
    _entities["background"]->setNbRect(1);
    _entities["background"]->_texture = std::make_shared<sf::Texture>();
    _entities["background"]->setTexture("assets/cenario/background.png");
    _entities["background"]->setSprite();
    _entities["background"]->setSpritePosition(sf::Vector2f(0, 0));

    _entities["listBackground"] = std::make_unique<Entity>();
    _entities["listBackground"]->setNbRect(1);
    _entities["listBackground"]->_texture = std::make_shared<sf::Texture>();
    _entities["listBackground"]->setTexture("assets/cenario/listMenu.png");
    _entities["listBackground"]->setSprite();
    _entities["listBackground"]->setSpriteOrigin();
    _entities["listBackground"]->setSpritePosition(sf::Vector2f(425, 280));

    _entities["pCreateInstanceButton"] = std::make_unique<Entity>();
    _entities["pCreateInstanceButton"]->setNbRect(1);
    _entities["pCreateInstanceButton"]->_texture = std::make_shared<sf::Texture>();
    _entities["pCreateInstanceButton"]->setTexture("assets/cenario/button.png");
    _entities["pCreateInstanceButton"]->setSprite();
    _entities["pCreateInstanceButton"]->setSpritePosition(sf::Vector2f(220, 100));
    _entities["pCreateInstanceButton"]->setSpriteScale(sf::Vector2f(1.5, 1.5));

    _texts["pCreateInstanceText"] = std::make_unique<sf::Text>();
    _texts["pCreateInstanceText"]->setFont(_font);
    _texts["pCreateInstanceText"]->setString("Create Instance");
    _texts["pCreateInstanceText"]->setCharacterSize(12);
    _texts["pCreateInstanceText"]->setPosition(sf::Vector2f(230, 108));

    _entities["pRefreshList"] = std::make_unique<Entity>();
    _entities["pRefreshList"]->setNbRect(1);
    _entities["pRefreshList"]->_texture = std::make_shared<sf::Texture>();
    _entities["pRefreshList"]->setTexture("assets/cenario/refreshButton.png");
    _entities["pRefreshList"]->setSprite();
    _entities["pRefreshList"]->setSpritePosition(sf::Vector2f(380, 100));
    _entities["pRefreshList"]->setSpriteScale(sf::Vector2f(1.5, 1.5));

    _entities["modalBackground"] = std::make_unique<Entity>();
    _entities["modalBackground"]->setNbRect(1);
    _entities["modalBackground"]->_texture = std::make_shared<sf::Texture>();
    _entities["modalBackground"]->setTexture("assets/cenario/listMenu.png");
    _entities["modalBackground"]->setSprite();
    _entities["modalBackground"]->setSpriteOrigin();
    _entities["modalBackground"]->setSpritePosition(sf::Vector2f(425, 280));

    _texts["modalTitle"] = std::make_unique<sf::Text>();
    _texts["modalTitle"]->setFont(_font);
    _texts["modalTitle"]->setString("Create Instance");
    _texts["modalTitle"]->setCharacterSize(20);
    _texts["modalTitle"]->setPosition(sf::Vector2f(500, 300));

    _entities["modalExitButton"] = std::make_unique<Entity>();
    _entities["modalExitButton"]->setNbRect(1);
    _entities["modalExitButton"]->_texture = std::make_shared<sf::Texture>();
    _entities["modalExitButton"]->setTexture("assets/cenario/button.png");
    _entities["modalExitButton"]->setSprite();
    _entities["modalExitButton"]->setSpritePosition(sf::Vector2f(300, 300));
    _entities["modalExitButton"]->setSpriteScale(sf::Vector2f(1.5, 1.5));

    _texts["modalExitButtonText"] = std::make_unique<sf::Text>();
    _texts["modalExitButtonText"]->setFont(_font);
    _texts["modalExitButtonText"]->setString("Cancel");
    _texts["modalExitButtonText"]->setCharacterSize(12);
    _texts["modalExitButtonText"]->setPosition(sf::Vector2f(230, 108));

    // gap between each instance button is 90 pixels in y
    Instance mockInstance1 = {"mockInstance1", "pong", 1, 2, 4210, 0};
    Instance mockInstance2 = {"mockInstance2", "rType", 1, 4, 4211, 1};
    _instanceButtons[0] = std::make_unique<InstanceButton>(mockInstance1, 225, 140);
    _instanceButtons[1] = std::make_unique<InstanceButton>(mockInstance2, 225, 230);
}

InstanceMenu::~InstanceMenu() {
    _window.close();
}

void InstanceMenu::mainloop() {
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            sf::Vector2f worldMousePosition = _window.mapPixelToCoords(mousePosition);

            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                for (auto& instanceButton : _instanceButtons) {
                    std::string key =
                        "submitButton" + std::to_string(instanceButton.second.get()->getId());
                    Entity* submitButton = instanceButton.second.get()->getSubmitButton();
                    if (submitButton->getSprite().getGlobalBounds().contains(worldMousePosition)) {
                        std::cout << "join instance " << instanceButton.second.get()->getId()
                                  << std::endl;
                        int port = instanceButton.second.get()->getPort();
                        _game.get()->connectToUdpServer(_game->getHost(), port);
                        return;
                    }
                }
                if (_entities["pRefreshList"]->getSprite().getGlobalBounds().contains(
                        worldMousePosition)) {
                    std::cout << "refresh list" << std::endl;
                    // TODO: Send a request to get new list of instances
                }

                if (_entities["pCreateInstanceButton"]->getSprite().getGlobalBounds().contains(
                        worldMousePosition)) {
                    std::cout << "can see the modal to create a new game instance" << std::endl;
                    _openInstanceModal = true;
                }

                if (_openInstanceModal &&
                    _entities["modalExitButton"]->getSprite().getGlobalBounds().contains(
                        worldMousePosition)) {
                    std::cout << "close the modal " << std::endl;  // TODO: remove
                    _openInstanceModal = false;
                }
            }
        }

        _window.clear();
        _window.setView(_view);
        _window.draw(_entities["background"]->getSprite());
        if (!_openInstanceModal) {
            _window.draw(_entities["listBackground"]->getSprite());
            _window.draw(_entities["pCreateInstanceButton"]->getSprite());
            _window.draw(_entities["pRefreshList"]->getSprite());
            _window.draw(*_texts["pCreateInstanceText"]);
            for (auto& instanceButton : _instanceButtons) {
                for (auto& entity : instanceButton.second->getEntities()) {
                    _window.draw(entity.second->getSprite());
                }
                for (auto& text : instanceButton.second->getTexts())
                    _window.draw(*text.second);
            }
        }
        if (_openInstanceModal) {
            _window.draw(_entities["modalBackground"]->getSprite());
            _window.draw(*_texts["modalTitle"]);
            _window.draw(_entities["modalExitButton"]->getSprite());
            _window.draw(*_texts["modalExitButtonText"]);
        }
        if (!_errorConnect)
            _window.draw(*_texts["ErrorConnexion"]);
        _window.display();
    }
}
