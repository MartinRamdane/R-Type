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
#include <string.h>

int getParam(char **av)
{
    if (strstr(av[1], "-sfml") != NULL)
        return (1);
    if (strstr(av[1], "-sdl") != NULL)
        return (2);
    return (1);
}

int main(int ac, char **av)
{
    struct Login login;
    std::shared_ptr<Game> game = std::make_shared<Game>();
    int param = getParam(av);
    // game->setType(param);
    Menu *menu = new Menu(game);
    menu->mainloop();
    delete menu;
    game->run();
    return 0;
}
