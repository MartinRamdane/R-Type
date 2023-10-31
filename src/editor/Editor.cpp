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
    _entitiesJsonConfig["flyer"] = "Flyer.rType.json";

    _entitiesSelectMenu["OrangeRobot"] = std::make_unique<Entity>(_ressourceManager);
    _entitiesSelectMenu["OrangeRobot"]->setTexture("OrangeRobot.png");
    _entitiesJsonConfig["OrangeRobot"] = "OrangeRobot.rType.json";

    _entitiesSelectMenu["bomberman"] = std::make_unique<Entity>(_ressourceManager);
    _entitiesSelectMenu["bomberman"]->setTexture("bomberman.png");
    _entitiesJsonConfig["bomberman"] = "Bomberman.rType.json";

    _entitiesSelectMenu["robot_type_5"] = std::make_unique<Entity>(_ressourceManager);
    _entitiesSelectMenu["robot_type_5"]->setTexture("robot_type_5.png");

    _entitiesSelectMenu["worm"] = std::make_unique<Entity>(_ressourceManager);
    _entitiesSelectMenu["worm"]->setTexture("worm.png");
    _entitiesJsonConfig["worm"] = "Worm.rType.json";

    _entitiesSelectMenu["dropper"] = std::make_unique<Entity>(_ressourceManager);
    _entitiesSelectMenu["dropper"]->setTexture("dropper.png");
    _entitiesJsonConfig["dropper"] = "Dropper.rType.json";

    //create Rects
    _entitiesRect["flyer"] = std::make_tuple(8, 0);
    _entitiesRect["OrangeRobot"] = std::make_tuple(2, 0);
    _entitiesRect["bomberman"] = std::make_tuple(7, 0);
    _entitiesRect["robot_type_5"] = std::make_tuple(3, 0);
    _entitiesRect["worm"] = std::make_tuple(6, 0);
    _entitiesRect["dropper"] = std::make_tuple(12, 0);

    _entityQuantity["background"] = 0;

    for (auto& entity : _entitiesSelectMenu) {
        entity.second->setRect(std::get<0>(_entitiesRect[entity.first]),
                               std::get<1>(_entitiesRect[entity.first]));
    }
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
            _selectedEntity = "bomberman";
        } else if (event.key.code == sf::Keyboard::Num5) {
            _selectedEntity = "worm";
        } else if (event.key.code == sf::Keyboard::Num6) {
            _selectedEntity = "dropper";
        } else if (event.key.code == sf::Keyboard::S) {
            std::cout << "Saving..." << std::endl;
            _savingMode = true;
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
            _entities[_selectedEntity + std::to_string(_entityQuantity[_selectedEntity])]->setRect(
                std::get<0>(_entitiesRect[_selectedEntity]),
                std::get<1>(_entitiesRect[_selectedEntity]));
            _entityQuantity[_selectedEntity]++;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);
            sf::Vector2f worldPosition = _window.mapPixelToCoords(mousePosition);

            for (auto it = _entities.begin(); it != _entities.end();) {
                if (it->first == "background") {
                    it++;
                    continue;
                }
                if (it->second->getSprite().getGlobalBounds().contains(worldPosition)) {
                    it = _entities.erase(it);
                    _entityQuantity[_selectedEntity]--;
                } else {
                    it++;
                }
            }
        }
    }
}

void Editor::update() {}

void Editor::saveLevel() {
    nlohmann::json level = JsonParser::readFile("rTypeLevels.json");

    std::cout << level[_levelName] << std::endl;
    int i = 1;
    level[_levelName] = {};
    for (auto entity : _entityQuantity) {
        if (entity.first == "background") {
            level[_levelName]["Entity" + std::to_string(i)]["Type"] = "Background";
        } else {
            if (entity.second == 0)
                continue;
            level[_levelName]["Entity" + std::to_string(i)]["Count"] = entity.second;
            level[_levelName]["Entity" + std::to_string(i)]["Config"] =
                _entitiesJsonConfig[entity.first];
            for (int j = 0; j <= entity.second; j++) {
                if (entity.first == "background" ||
                    _entities.find(entity.first + std::to_string(j)) == _entities.end())
                    continue;
                std::cout << entity.first + std::to_string(j) << std::endl;
                level[_levelName]["Entity" + std::to_string(i)]["Positions"][j]["X"] =
                    _entities[entity.first + std::to_string(j)]->getSprite().getPosition().x;
                level[_levelName]["Entity" + std::to_string(i)]["Positions"][j]["Y"] =
                    _entities[entity.first + std::to_string(j)]->getSprite().getPosition().y;
            }
        }
        i++;
    }

    std::string jsonString = level.dump(2);
    std::cout << jsonString << std::endl;
    std::ofstream file("./config/r-type/rTypeLevels.json");
    file << jsonString;
}

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
        _window.draw(_entities["background"]->getSprite());
        for (auto& entity : _entities) {
            if (entity.first == "background")
                continue;
            _window.draw(entity.second->getSprite());
        }
        _window.setView(_menuView);
        for (auto& text : _texts) {
            _window.draw(*text.second);
        }
        _window.draw(_entitiesSelectMenu[_selectedEntity]->getSprite());
        if (_savingMode) {
            std::cout << "Enter level name: \nExample: Level-1\n";
            std::cin >> _levelName;
            saveLevel();
            _savingMode = false;
        }
        _window.display();
    }
}
