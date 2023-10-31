/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Editor
*/

#ifndef Editor_HPP_
#define Editor_HPP_

#include <map>
#include <memory>
#include "../../client/SFML/Entity.hpp"

class Editor {
   public:
    Editor();
    ~Editor();
    void mainloop();

   private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Font _font;
    std::map<std::string, std::unique_ptr<Entity>> _entities;
    std::map<std::string, std::unique_ptr<sf::Text>> _texts;
    bool _errorConnect = true;
};

#endif /* !Editor_HPP_ */
