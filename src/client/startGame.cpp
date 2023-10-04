/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** startGame.cpp
*/

#include "Login.hpp"
#include "Entity.hpp"
#include "Input.hpp"

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

    Input nameInput = Input("assets/cenario/TextInput.png", "assets/cenario/TextInputHover.png", "Name");
    nameInput.setSpritePosition(sf::Vector2f(300, 170));
    nameInput.setSpriteScale(sf::Vector2f(2.5, 2.5));

    Input portInput = Input("assets/cenario/TextInput.png", "assets/cenario/TextInputHover.png", "Port");
    portInput.setSpritePosition(sf::Vector2f(300, 230));
    portInput.setSpriteScale(sf::Vector2f(2.5, 2.5));

    Input ipInput = Input("assets/cenario/TextInput.png", "assets/cenario/TextInputHover.png", "IP Adress");
    ipInput.setSpritePosition(sf::Vector2f(300, 290));
    ipInput.setSpriteScale(sf::Vector2f(2.5, 2.5));

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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            nameInput.eventHandler(event, window);
            portInput.eventHandler(event, window);
            ipInput.eventHandler(event, window);
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);

            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (connect.getGlobalBounds().contains(worldMousePosition))
                {
                    login.name = nameInput.getText();
                    login.port = portInput.getText();
                    login.ip = ipInput.getText();
                    window.close();
                    return login;
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && ipInput.getActive())
            {
                if (nameInput.getText() != "" && portInput.getText() != "" && ipInput.getText() != "")
                {
                    login.name = nameInput.getText();
                    login.port = portInput.getText();
                    login.ip = ipInput.getText();
                    window.close();
                    return login;
                }
            }
            if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Tab || event.key.code == sf::Keyboard::Return))
            {
                if (nameInput.getActive())
                {
                    nameInput.setActive(false);
                    portInput.setActive(true);
                }
                else if (portInput.getActive())
                {
                    portInput.setActive(false);
                    ipInput.setActive(true);
                }
                else if (ipInput.getActive())
                {
                    ipInput.setActive(false);
                    nameInput.setActive(true);
                }
            }
        }
        nameInput.update();
        portInput.update();
        ipInput.update();

        window.clear();
        window.setView(_view);
        window.draw(background.getSprite());
        window.draw(logo.getSprite());
        nameInput.draw(window);
        portInput.draw(window);
        ipInput.draw(window);
        window.draw(connectButton.getSprite());
        window.draw(connect);

        window.display();
    }
    return login;
}
