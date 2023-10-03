/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** startGame.cpp
*/

#include "Login.hpp"
#include "Entity.hpp"

Login startgame()
{
    struct Login login;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "My window");
    sf::View _view = sf::View(sf::FloatRect(0, 0, 850, 478));

    sf::Font font;
    if (!font.loadFromFile("font/pixel.ttf"))
        std::cerr << "Error: could not load font" << std::endl;

    Entity background;
    background._nbRect = 1;
    background._texture = std::make_shared<sf::Texture>();
    background.setTexture("assets/cenario/background.png");
    background.setSprite();
    background.setSpritePosition(sf::Vector2f(0, 0));

   Entity logo;
    logo._nbRect = 1;
    logo._texture = std::make_shared<sf::Texture>();
    logo.setTexture("assets/cenario/Logo.png");
    logo.setSprite();
    logo.setSpritePosition(sf::Vector2f(425, 100));
    logo.setSpriteOrigin();

    Entity nameInput;
    nameInput._nbRect = 1;
    nameInput._texture = std::make_shared<sf::Texture>();
    nameInput.setTexture("assets/cenario/TextInput.png");
    nameInput.setSprite();
    nameInput.setSpritePosition(sf::Vector2f(425, 200));
    nameInput.setSpriteScale(sf::Vector2f(2.5, 2.5));
    nameInput.setSpriteOrigin();

    Entity portInput;
    portInput._nbRect = 1;
    portInput._texture = std::make_shared<sf::Texture>();
    portInput.setTexture("assets/cenario/TextInput.png");
    portInput.setSprite();
    portInput.setSpritePosition(sf::Vector2f(425, 260));
    portInput.setSpriteScale(sf::Vector2f(2.5, 2.5));
    portInput.setSpriteOrigin();

    Entity ipInput;
    ipInput._nbRect = 1;
    ipInput._texture = std::make_shared<sf::Texture>();
    ipInput.setTexture("assets/cenario/TextInput.png");
    ipInput.setSprite();
    ipInput.setSpritePosition(sf::Vector2f(425, 320));
    ipInput.setSpriteScale(sf::Vector2f(2.5, 2.5));
    ipInput.setSpriteOrigin();

    Entity connectButton;
    connectButton._nbRect = 1;
    connectButton._texture = std::make_shared<sf::Texture>();
    connectButton.setTexture("assets/cenario/button.png");
    connectButton.setSprite();
    connectButton.setSpritePosition(sf::Vector2f(425, 380));
    connectButton.setSpriteScale(sf::Vector2f(2.5, 2.5));
    connectButton.setSpriteOrigin();

    sf::Text connect;
    connect.setFont(font);
    connect.setString("connect");
    connect.setCharacterSize(20);
    connect.setFillColor(sf::Color::White);
    connect.setPosition(sf::Vector2f(425, 380));
    connect.setOrigin(sf::Vector2f(connect.getLocalBounds().width / 2, connect.getLocalBounds().height / 2));

    sf::Text name;
    name.setFont(font);
    name.setString("enter your name");
    name.setCharacterSize(20);
    name.setFillColor(sf::Color::White);
    name.setPosition(sf::Vector2f(425, 200));
    name.setOrigin(sf::Vector2f(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2));

    sf::String nameInputText;
    bool isNameEditing = false;

    sf::Text port;
    port.setFont(font);
    port.setString("enter the port");
    port.setCharacterSize(20);
    port.setFillColor(sf::Color::White);
    port.setPosition(sf::Vector2f(425, 260));
    port.setOrigin(sf::Vector2f(port.getLocalBounds().width / 2, port.getLocalBounds().height / 2));

    sf::String portInputText;
    bool isPortEditing = false;

    sf::Text ip;
    ip.setFont(font);
    ip.setString("enter ip address");
    ip.setCharacterSize(20);
    ip.setFillColor(sf::Color::White);
    ip.setPosition(sf::Vector2f(425, 320));
    ip.setOrigin(sf::Vector2f(ip.getLocalBounds().width / 2, ip.getLocalBounds().height / 2));

    sf::String ipInputText;
    bool isIpEditing = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (name.getGlobalBounds().contains(worldMousePosition)) {
                    isNameEditing = true;
                    isIpEditing = false;
                    isPortEditing = false;
                } if (port.getGlobalBounds().contains(worldMousePosition)) {
                    isPortEditing = true;
                    isNameEditing = false;
                    isIpEditing = false;
                } if (ip.getGlobalBounds().contains(worldMousePosition)) {
                    isIpEditing = true;
                    isNameEditing = false;
                    isPortEditing = false;
                } if (connect.getGlobalBounds().contains(worldMousePosition)) {
                    login.name = nameInputText;
                    login.port = portInputText;
                    login.ip = ipInputText;
                    window.close();
                    return login;
                }
            }
            else if (event.type == sf::Event::TextEntered && isNameEditing)
            {
                if (event.text.unicode == 8 && nameInputText.getSize() > 0) // Touche de retour arrière (backspace)
                    nameInputText.erase(nameInputText.getSize() - 1);
                else if (event.text.unicode == 10 || event.text.unicode == 13) { // Touche entrée
                    isNameEditing = false;
                    login.name = nameInputText;
                } else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Caractères imprimables
                    nameInputText += event.text.unicode;
                name.setString(nameInputText);
            }
            else if (event.type == sf::Event::TextEntered && isPortEditing)
            {
                if (event.text.unicode == 8 && portInputText.getSize() > 0) // Touche de retour arrière (backspace)
                    portInputText.erase(portInputText.getSize() - 1);
                else if (event.text.unicode == 10 || event.text.unicode == 13) { // Touche entrée
                        isPortEditing = false;
                    login.port = portInputText;
                } else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Caractères imprimables
                    portInputText += event.text.unicode;
                port.setString(portInputText);
            }
            else if (event.type == sf::Event::TextEntered && isIpEditing)
            {
                if (event.text.unicode == 8 && ipInputText.getSize() > 0) // Touche de retour arrière (backspace)
                    ipInputText.erase(ipInputText.getSize() - 1);
                else if (event.text.unicode == 10 || event.text.unicode == 13) { // Touche entrée
                        isIpEditing = false;
                    login.ip = ipInputText;
                } else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Caractères imprimables
                    ipInputText += event.text.unicode;
                ip.setString(ipInputText);
            }
        }

        window.clear();
        window.setView(_view);
        window.draw(background.getSprite());
        window.draw(logo.getSprite());
        window.draw(nameInput.getSprite());
        window.draw(name);
        window.draw(portInput.getSprite());
        window.draw(port);
        window.draw(ipInput.getSprite());
        window.draw(ip);
        window.draw(connectButton.getSprite());
        window.draw(connect);

        window.display();
    }
    return login;
}
