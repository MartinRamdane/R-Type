/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySDL.hpp
*/

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../UDPClient.hpp"
#include "RessourceManagerSFML.hpp"

class DisplaySDL : public IDisplay {
   public:
    DisplaySDL();
    ~DisplaySDL();
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
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    Camera _camera;
    SDL_Event _event;
    std::shared_ptr<RessourceManagerSDL> _ressourceManager;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    bool closed = false;
    std::vector<std::string> _events;
};