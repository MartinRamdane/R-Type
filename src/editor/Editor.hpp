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
#include <tuple>
#include "../client/SFML/EntitySFML.hpp"
#include "../global/JsonParser.hpp"
#include "../client/Input.hpp"

class Editor {
   public:
    Editor();
    ~Editor();
    void keyEvent(sf::Event event);
    void mouseEvent(sf::Event event);
    void mainloop();
    void update();
    void saveLevel();
    void getInput();

   private:
    std::shared_ptr<sf::RenderWindow> _window;
    sf::View _mainView;
    sf::View _menuView;
    sf::Font _font;
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::map<std::string, std::unique_ptr<EntitySFML>> _entities;
    std::map<std::string, std::unique_ptr<EntitySFML>> _entitiesSelectMenu;
    std::unique_ptr<EntitySFML> _saveButton;
    std::unique_ptr<EntitySFML> _music1;
    std::unique_ptr<EntitySFML> _music2;
    std::map<std::string, std::tuple<int, int>> _entitiesRect;
    std::map<std::string, std::string> _entitiesJsonConfig;
    std::map<std::string, int> _entityQuantity;
    std::map<std::string, std::unique_ptr<sf::Text>> _texts;
    std::shared_ptr<RessourceManagerSFML> _ressourceManager;
    std::map<std::string, std::unique_ptr<Input>> _inputs;
    std::map<std::string, sf::Music> _musics;
    std::string _selectedEntity = "flyer";
    bool _savingMode = false;
    std::string _levelName;
    JsonParser _jsonParser;
    int _x = 0;
    int _y = 0;
    std::string _selectedMusic = "level1.ogg";
};

#endif /* !Editor_HPP_ */
