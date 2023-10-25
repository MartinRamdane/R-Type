/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "Login.hpp"
#include <map>
#include <memory>
#include "Input.hpp"
#include "SFML/Entity.hpp"
#include "Game.hpp"

class Menu
{
public:
    Menu(std::shared_ptr<Game> &game);
    ~Menu();

    void mainloop();

private:
    struct Login _login;
    sf::RenderWindow _window;
    sf::View _view;
    sf::Font _font;
    std::map<std::string, std::unique_ptr<Entity>> _entities;
    std::map<std::string, std::unique_ptr<Input>> _inputs;
    std::map<std::string, std::unique_ptr<sf::Text>> _texts;
    bool _errorConnect = true;
    std::shared_ptr<Game> _game;
};

#endif /* !MENU_HPP_ */
