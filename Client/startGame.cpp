/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** startGame.cpp
*/

#include "include.hpp"
#include "Entity.hpp"

Login startgame()
{
    struct Login login;
    // sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // sf::Font font;
    // if (!font.loadFromFile("../font/pixel.ttf"))
    //     std::cerr << "Error: could not load font" << std::endl;

    // Entity background;
    // background.setSprite("../sprites/background.png");
    // background.setSpritePosition(sf::Vector2f(0, 0));
    // background.setSpriteScaleToWindow(window);

    // Entity logo;
    // logo.setSprite("../sprites/Logo.png");
    // logo.setSpritePosition(sf::Vector2f(400, 100));
    // logo.setSpriteOrigin();

    // Entity nameInput;
    // nameInput.setSprite("../sprites/TextInput.png");
    // nameInput.setSpritePosition(sf::Vector2f(400, 220));
    // nameInput.setSpriteScale(sf::Vector2f(2.5, 2.5));
    // nameInput.setSpriteOrigin();

    // Entity portInput;
    // portInput.setSprite("../sprites/TextInput.png");
    // portInput.setSpritePosition(sf::Vector2f(400, 300));
    // portInput.setSpriteScale(sf::Vector2f(2.5, 2.5));
    // portInput.setSpriteOrigin();

    // Entity ipInput;
    // ipInput.setSprite("../sprites/TextInput.png");
    // ipInput.setSpritePosition(sf::Vector2f(400, 380));
    // ipInput.setSpriteScale(sf::Vector2f(2.5, 2.5));
    // ipInput.setSpriteOrigin();

    // Entity connectButton;
    // connectButton.setSprite("../sprites/button.png");
    // connectButton.setSpritePosition(sf::Vector2f(400, 460));
    // connectButton.setSpriteScale(sf::Vector2f(2.5, 2.5));
    // connectButton.setSpriteOrigin();

    // sf::Text connect;
    // connect.setFont(font);
    // connect.setString("connect");
    // connect.setCharacterSize(20);
    // connect.setFillColor(sf::Color::White);
    // connect.setPosition(sf::Vector2f(400, 460));
    // connect.setOrigin(sf::Vector2f(connect.getLocalBounds().width / 2, connect.getLocalBounds().height / 2));

    // sf::Text name;
    // name.setFont(font);
    // name.setString("enter your name");
    // name.setCharacterSize(20);
    // name.setFillColor(sf::Color::White);
    // name.setPosition(sf::Vector2f(400, 220));
    // name.setOrigin(sf::Vector2f(name.getLocalBounds().width / 2, name.getLocalBounds().height / 2));

    // sf::String nameInputText;
    // bool isNameEditing = false;

    // sf::Text port;
    // port.setFont(font);
    // port.setString("enter the port");
    // port.setCharacterSize(20);
    // port.setFillColor(sf::Color::White);
    // port.setPosition(sf::Vector2f(400, 300));
    // port.setOrigin(sf::Vector2f(port.getLocalBounds().width / 2, port.getLocalBounds().height / 2));

    // sf::String portInputText;
    // bool isPortEditing = false;

    // sf::Text ip;
    // ip.setFont(font);
    // ip.setString("enter ip address");
    // ip.setCharacterSize(20);
    // ip.setFillColor(sf::Color::White);
    // ip.setPosition(sf::Vector2f(400, 380));
    // ip.setOrigin(sf::Vector2f(ip.getLocalBounds().width / 2, ip.getLocalBounds().height / 2));

    // sf::String ipInputText;
    // bool isIpEditing = false;

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //         {
    //             window.close();
    //         }

    //         else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    //         {
    //             if (name.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
    //                 isNameEditing = true;
    //             if (port.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
    //                 isPortEditing = true;
    //             if (ip.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
    //                 isIpEditing = true;
    //             if (connect.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
    //                 login.name = nameInputText;
    //                 login.port = portInputText;
    //                 login.ip = ipInputText;
    //                 window.close();
    //                 return login;
    //             }
    //         }
    //         else if (event.type == sf::Event::TextEntered && isNameEditing)
    //         {
    //             if (event.text.unicode == 8 && nameInputText.getSize() > 0) // Touche de retour arrière (backspace)
    //                 nameInputText.erase(nameInputText.getSize() - 1);
    //             else if (event.text.unicode == 10) { // Touche entrée
    //                 isNameEditing = false;
    //                 login.name = nameInputText;
    //             } else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Caractères imprimables
    //                 nameInputText += event.text.unicode;
    //             name.setString(nameInputText);
    //         }
    //         else if (event.type == sf::Event::TextEntered && isPortEditing)
    //         {
    //             if (event.text.unicode == 8 && portInputText.getSize() > 0) // Touche de retour arrière (backspace)
    //                 portInputText.erase(portInputText.getSize() - 1);
    //             else if (event.text.unicode == 10) { // Touche entrée
    //                 isPortEditing = false;
    //                 login.port = portInputText;
    //             } else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Caractères imprimables
    //                 portInputText += event.text.unicode;
    //             port.setString(portInputText);
    //         }
    //         else if (event.type == sf::Event::TextEntered && isIpEditing)
    //         {
    //             if (event.text.unicode == 8 && ipInputText.getSize() > 0) // Touche de retour arrière (backspace)
    //                 ipInputText.erase(ipInputText.getSize() - 1);
    //             else if (event.text.unicode == 10) { // Touche entrée
    //                 isIpEditing = false;
    //                 login.ip = ipInputText;
    //             } else if (event.text.unicode >= 32 && event.text.unicode <= 126) // Caractères imprimables
    //                 ipInputText += event.text.unicode;
    //             ip.setString(ipInputText);
    //         }
    //     }

    //     window.clear();
    //     window.draw(background.getSprite());
    //     window.draw(logo.getSprite());
    //     window.draw(nameInput.getSprite());
    //     window.draw(name);
    //     window.draw(portInput.getSprite());
    //     window.draw(port);
    //     window.draw(ipInput.getSprite());
    //     window.draw(ip);
    //     window.draw(connectButton.getSprite());
    //     window.draw(connect);

    //     window.display();
    // }

    return login;
}
