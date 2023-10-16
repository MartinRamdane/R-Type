/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** main.cpp
*/

#include "Game.hpp"
#include "Login.hpp"
#include "Parser.hpp"
#include <thread>
#include <memory>
#include "Menu.hpp"

int main()
{
    struct Login login;
    std::shared_ptr<Game> game = std::make_shared<Game>();
    Menu *menu = new Menu(game);
    menu->mainloop();
    delete menu;
    game->run();
    return 0;
}
