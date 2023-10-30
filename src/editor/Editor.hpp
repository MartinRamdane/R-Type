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
#include "../client/SFML/Entity.hpp"

class Editor {
   public:
    Editor();
    ~Editor();
    void keyEvent(sf::Event event);
    void mouseEvent(sf::Event event);
    void mainloop();
    void update();

   private:
    sf::RenderWindow _window;
    sf::View _mainView;
    sf::View _menuView;
    sf::Font _font;
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::map<std::string, std::unique_ptr<Entity>> _entities;
    std::map<std::string, std::unique_ptr<Entity>> _entitiesSelectMenu;
    std::map<std::string, int> _entityQuantity;
    std::map<std::string, std::unique_ptr<sf::Text>> _texts;
    std::shared_ptr<RessourceManager> _ressourceManager;
    std::string _selectedEntity = "flyer";
};

#endif /* !Editor_HPP_ */
