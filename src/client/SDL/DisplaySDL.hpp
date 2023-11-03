/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySDL.hpp
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../UDPClient.hpp"
#include "RessourceManagerSDL.hpp"
#include "EntitySDL.hpp"
#include "../IDisplay.hpp"

class DisplaySDL : public IDisplay {
   public:
    DisplaySDL();
    ~DisplaySDL();
    void createWindow(std::string name, int x, int y);
    void draw(std::map<int, std::shared_ptr<IEntity>>* _entities);
    void handleEvent();
    bool getClosed() const { return closed; };
    bool windowIsOpen() const { return _windowClosed; };
    std::vector<std::string> getEvents();
    std::shared_ptr<IEntity> createEntity(IEntity::EntityInfos entityInfos);
    std::shared_ptr<IEntity> createSprite(IEntity::EntityInfos entityInfos);
    std::shared_ptr<IEntity> createText(IEntity::EntityInfos entityInfos);
    void closeWindow() {  };

   private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;
    SDL_Event _event;
    std::shared_ptr<RessourceManagerSDL> _ressourceManager;
    std::chrono::high_resolution_clock::time_point _lastFrameTime;
    bool closed = false;
    bool _windowClosed = true;
    std::vector<std::string> _events;
};