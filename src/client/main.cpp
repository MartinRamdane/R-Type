/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** main.cpp
*/

#include <string.h>
#include <memory>
#include <thread>
#include "Game.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "InstanceMenu.hpp"
#include "Parser.hpp"

int getParam(char **av) {
    if (strstr(av[1], "-sfml") != NULL)
        return (1);
    if (strstr(av[1], "-sdl") != NULL)
        return (2);
    return (1);
}

int main(int ac, char **av) {
    struct Login login;
    std::shared_ptr <Game> game = std::make_shared<Game>();
    int param = 0;
    if (ac == 1) {
        std::cout << "Usage: ./client [lib]" << std::endl;
        std::cout << "Lib: -sfml or -sdl" << std::endl;
        return 84;
    } else {
        param = getParam(av);
    }
    game->setLib(param);
    Menu *menu = new Menu(game);
    std::shared_ptr<sf::RenderWindow> window = menu->mainloop();
    delete menu;
    game->run(window);
    return 0;
}
