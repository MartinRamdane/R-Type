/*
** EPITECH PROJECT, 2023
** Input.hpp
** File description:
** Input
*/

#ifndef INPUT_HEADER_GUARD
#define INPUT_HEADER_GUARD
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include <memory>
#include "SFML/RessourceManager.hpp"

class Input {
   public:
    Input(std::string texture, std::string textureHover, std::string textValue, std::shared_ptr<RessourceManager> ressourceManager);
    ~Input(){};
    void createSprite();
    void setSpriteRect(sf::IntRect rect);
    void setSpritePosition(sf::Vector2f pos);
    void setSpriteScale(sf::Vector2f scale);
    void setSpriteOrigin();
    void setSpriteRotation(float angle);
    void setSpriteTexture(std::shared_ptr<sf::Texture>& texture);
    void draw(sf::RenderWindow& window);
    void eventHandler(sf::Event event, sf::RenderWindow& window);
    void update();
    std::string getText() { return _value; };
    sf::Vector2f getSpritePosition();
    bool getActive() const { return _isActive; };
    void setActive(bool active) { _isActive = active; };
    void setFont(sf::Font font) {
        _font = font;
        _text.setFont(_font);
    };

   protected:
   private:
    std::string _value;
    std::string _textureFile;
    std::string _textureFileHover;
    sf::Texture _texture;
    sf::Texture _textureHover;
    sf::Sprite _sprite;
    bool _isActive = false;
    static std::map<sf::Keyboard::Key, std::string> keys;
    sf::Font _font;
    sf::Text _text;
    bool _hover;
    sf::RectangleShape cursor;
    sf::Clock clock;
    bool cursorVisible = false;
    std::string _textValue;
    sf::Sound _inputHoverSound;
};

#endif /* !INPUT_HEADER_GUARD */
