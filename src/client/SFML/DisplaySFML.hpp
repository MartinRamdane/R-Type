/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySFML.hpp
*/

#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../IDisplay.hpp"
#include "../TCPClientImpl.hpp"
#include "../UDPClient.hpp"
#include "RessourceManager.hpp"

class DisplaySFML : public IDisplay {
   public:
    DisplaySFML();
    ~DisplaySFML();
    void createWindow(std::string name, int x, int y);
    void draw(std::map<int, std::shared_ptr<IEntity>>* _entities);
    void handleEvent();
    bool getClosed() const { return closed; };
    bool windowIsOpen() const { return _window.isOpen(); };
    std::vector<std::string> getEvents();
    std::shared_ptr<IEntity> createEntity(IEntity::EntityInfos entityInfos);
    std::shared_ptr<IEntity> createSprite(IEntity::EntityInfos entityInfos);
    std::shared_ptr<IEntity> createText(IEntity::EntityInfos entityInfos);

   private:
    sf::RenderWindow _window;
    sf::View _view;
    sf::Event _event;
    std::shared_ptr<RessourceManager> _ressourceManager;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    bool closed = false;
    std::vector<std::string> _events;
};