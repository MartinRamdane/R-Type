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
#include "SFML/Entity.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "InstanceButton.hpp"
#include "Login.hpp"
#include "SFML/RessourceManager.hpp"
#include "IDisplay.hpp"

class InstanceMenu {
public:
    InstanceMenu(Game *game);

    ~InstanceMenu();

    void mainloop();

private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Font _font;
    std::map <std::string, std::unique_ptr<Entity>> _entities;
    std::map <std::string, std::unique_ptr<sf::Text>> _texts;
    std::map <std::string, std::unique_ptr<Entity>> _gameSelector;
    bool _errorConnect = true;
    std::shared_ptr <Game> _game;
    bool _openInstanceModal = false;
    std::map<int, std::unique_ptr<InstanceButton>> _instanceButtons;
};

#endif /* !INSTANCE_MENU_HPP_ */
