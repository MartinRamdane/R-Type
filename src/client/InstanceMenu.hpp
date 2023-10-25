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
#include "Entity.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Login.hpp"

class InstanceMenu {
   public:
    InstanceMenu(std::shared_ptr<Game>& game);
    ~InstanceMenu();

    void mainloop();

   private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Font _font;
    std::map<std::string, std::unique_ptr<Entity>> _entities;
    std::map<std::string, std::unique_ptr<sf::Text>> _texts;
    bool _errorConnect = true;
    std::shared_ptr<Game> _game;
};

#endif /* !INSTANCE_MENU_HPP_ */
