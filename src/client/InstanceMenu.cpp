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

    // gap between each instance button is 90 pixels in y
    Instance mockInstance1 = {"mockInstance1", "pong", 1, 2, 4210, 0};
    Instance mockInstance2 = {"mockInstance2", "rType", 1, 4, 4211, 1};
    _instanceButtons[0] = std::make_unique<InstanceButton>(mockInstance1, 225, 200);
    _instanceButtons[1] = std::make_unique<InstanceButton>(mockInstance2, 225, 290);
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
                    }
                }
                std::cout << "handle mouse pressed" << std::endl;
            }
        }

        _window.clear();
        _window.setView(_view);
        _window.draw(_entities["background"]->getSprite());
        _window.draw(_entities["listBackground"]->getSprite());
        if (!_errorConnect)
            _window.draw(*_texts["ErrorConnexion"]);
        for (auto& instanceButton : _instanceButtons) {
            for (auto& entity : instanceButton.second->getEntities()) {
                _window.draw(entity.second->getSprite());
            }
            for (auto& text : instanceButton.second->getTexts())
                _window.draw(*text.second);
        }
        _window.display();
    }
}
