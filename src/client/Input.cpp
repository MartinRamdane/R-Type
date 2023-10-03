/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-martin.ramdane
** File description:
** Input
*/

#include "Input.hpp"

Input::Input(std::string texture, std::string textureHover, std::string textValue) : _textureFile(texture), _textureFileHover(textureHover)
{
    _textValue = textValue;
    this->_font.loadFromFile(std::string("font/pixel.ttf"));
    _text = sf::Text();
    _text.setFont(this->_font);
    _text.setCharacterSize(20);
    _text.setString(textValue);
    _hover = false;
    createSprite();
    cursor = sf::RectangleShape(sf::Vector2f(2, 24));
    cursor.setFillColor(sf::Color::White);
}

void Input::createSprite()
{
    _texture.loadFromFile(_textureFile);
    _textureHover.loadFromFile(_textureFileHover);
    _sprite.setTexture(_texture);
    // _sprite.setOrigin(_sprite.getLocalBounds().width / 2, _sprite.getLocalBounds().height / 2);
}

void Input::setSpriteRect(sf::IntRect rect)
{
    this->_sprite.setTextureRect(rect);
}

void Input::setSpritePosition(sf::Vector2f pos)
{
    this->_sprite.setPosition(pos);
    pos.x += 15;
    pos.y += 14;
    _text.setPosition(pos);
    cursor.setPosition(pos);
}

void Input::setSpriteScale(sf::Vector2f scale)
{
    this->_sprite.setScale(scale);
}

void Input::setSpriteOrigin()
{
    sf::Vector2f size = sf::Vector2f(_texture.getSize().x, _texture.getSize().y);
    this->_sprite.setOrigin(size.x / 2, size.y / 2);
}

void Input::setSpriteRotation(float angle)
{
    this->_sprite.setRotation(angle);
}

void Input::setSpriteTexture(std::shared_ptr<sf::Texture> &texture)
{
    this->_sprite.setTexture(*texture);
}

void Input::draw(sf::RenderWindow &window)
{
    if (_hover)
        _sprite.setTexture(_textureHover);
    else
        _sprite.setTexture(_texture);
    window.draw(this->_sprite);
    window.draw(this->_text);
    if (cursorVisible && _isActive)
        window.draw(cursor);
}

void Input::eventHandler(sf::Event event, sf::RenderWindow &window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF = window.mapPixelToCoords(mousePosition);

    if (_sprite.getGlobalBounds().contains(mousePosF))
    {
        _hover = true;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            this->_isActive = true;
            _hover = true;
        }
    }
    else
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            this->_isActive = false;
            this->_hover = false;
        }
        if (!this->_isActive)
            _hover = false;
    }
    if (this->_isActive)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Backspace && !this->_value.empty())
            this->_value = this->_value.substr(0, this->_value.size() - 1);
        if (event.type == sf::Event::TextEntered && event.text.unicode == '.')
            this->_value += ".";
        else if (event.type == sf::Event::KeyPressed && event.key.code != sf::Keyboard::Backspace)
        {
            event.type == sf::Event::KeyPressed ? this->_value += keys[event.key.code] : this->_value;
        }
    }
    if (_isActive)
        _text.setString(_value);
    else if (_value.empty())
        _text.setString(_textValue);
}

void Input::update()
{
    if (clock.getElapsedTime().asMilliseconds() > 500)
    {
        cursorVisible = !cursorVisible;
        clock.restart();
    }
    cursor.setPosition(sf::Vector2f(_text.getPosition().x + _text.getLocalBounds().width + 5, _text.getPosition().y));
}

sf::Vector2f Input::getSpritePosition()
{
    return _sprite.getPosition();
}

std::map<sf::Keyboard::Key, std::string> Input::keys = {
    {sf::Keyboard::A, "a"},
    {sf::Keyboard::B, "b"},
    {sf::Keyboard::C, "c"},
    {sf::Keyboard::D, "d"},
    {sf::Keyboard::E, "e"},
    {sf::Keyboard::F, "f"},
    {sf::Keyboard::G, "g"},
    {sf::Keyboard::H, "h"},
    {sf::Keyboard::I, "i"},
    {sf::Keyboard::J, "j"},
    {sf::Keyboard::K, "k"},
    {sf::Keyboard::L, "l"},
    {sf::Keyboard::M, "m"},
    {sf::Keyboard::N, "n"},
    {sf::Keyboard::O, "o"},
    {sf::Keyboard::P, "p"},
    {sf::Keyboard::Q, "q"},
    {sf::Keyboard::R, "r"},
    {sf::Keyboard::S, "s"},
    {sf::Keyboard::T, "t"},
    {sf::Keyboard::U, "u"},
    {sf::Keyboard::V, "v"},
    {sf::Keyboard::W, "w"},
    {sf::Keyboard::X, "x"},
    {sf::Keyboard::Y, "y"},
    {sf::Keyboard::Z, "z"},
    {sf::Keyboard::Space, " "},
    {sf::Keyboard::Num0, "0"},
    {sf::Keyboard::Num1, "1"},
    {sf::Keyboard::Num2, "2"},
    {sf::Keyboard::Num3, "3"},
    {sf::Keyboard::Num4, "4"},
    {sf::Keyboard::Quote, "4"},
    {sf::Keyboard::Num5, "5"},
    {sf::Keyboard::Num6, "6"},
    {sf::Keyboard::Num7, "7"},
    {sf::Keyboard::Num8, "8"},
    {sf::Keyboard::Num9, "9"},
    {sf::Keyboard::Numpad0, "0"},
    {sf::Keyboard::Numpad1, "1"},
    {sf::Keyboard::Numpad2, "2"},
    {sf::Keyboard::Numpad3, "3"},
    {sf::Keyboard::Numpad4, "4"},
    {sf::Keyboard::Numpad5, "5"},
    {sf::Keyboard::Numpad6, "6"},
    {sf::Keyboard::Numpad7, "7"},
    {sf::Keyboard::Numpad8, "8"},
    {sf::Keyboard::Numpad9, "9"},
};