/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** InstanceMenu
*/

#ifndef INSTANCE_MENU_HPP_
#define INSTANCE_MENU_HPP_

#include <map>
#include <memory>
#include "../types/Instance.hpp"
#include "SFML/EntitySFML.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "InstanceButton.hpp"
#include "Login.hpp"
#include "SFML/RessourceManagerSFML.hpp"
#include "IDisplay.hpp"

class InstanceMenu {
public:
    InstanceMenu(Game *game);

    ~InstanceMenu();

    void mainloop(std::shared_ptr<sf::RenderWindow> window);

    void addInstanceButton(InstanceType instance, int x,
                           int y);

private:
    std::shared_ptr<sf::RenderWindow> _window;
    sf::View _view;
    sf::Font _font;
    std::map <std::string, std::unique_ptr<EntitySFML>> _entities;
    std::map <std::string, std::unique_ptr<sf::Text>> _texts;
    std::map <std::string, std::unique_ptr<EntitySFML>> _gameSelector;
    bool _errorConnect = true;
    std::shared_ptr <Game> _game;
    bool _openInstanceModal = false;
    std::map<int, std::unique_ptr<InstanceButton>> _instanceButtons;
    std::shared_ptr <TCPClientImpl> _client;
    bool _windowCreated = false;
};

#endif /* !INSTANCE_MENU_HPP_ */
