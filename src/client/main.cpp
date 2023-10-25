/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** main.cpp
*/

#include <memory>
#include <thread>
#include "Game.hpp"
#include "InstanceMenu.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Parser.hpp"

int main() {
    struct Login login;
    std::shared_ptr<Game> game = std::make_shared<Game>();
    Menu* menu = new Menu(game);
    menu->mainloop();
    delete menu;
    InstanceMenu* instanceMenu = new InstanceMenu(game);
    instanceMenu->mainloop();
    delete instanceMenu;
    game->run();
    return 0;
}
