/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** main
*/

#include "Editor.hpp"

int main(int ac, char** av) {
    if (ac == 2 && std::string(av[1]) == "-h") {
        std::cout << "How to use the editor:\n"
                     "You can place sprites using the left click of your mouse and delete them "
                     "using the right click.\n"
                     "You can move the camera using the arrow keys.\n"
                        "You can change the sprite using the '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', ')' and '=' keys.\n"
                    "For saving the map, press 's' or click on the save button." << std::endl;
        return 0;
    }
    Editor editor;
    editor.mainloop();
    return 0;
}