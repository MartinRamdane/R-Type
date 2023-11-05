/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManagerSDL.hpp
*/

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class RessourceManagerSDL {
   public:
    RessourceManagerSDL(SDL_Renderer* renderer);
    ~RessourceManagerSDL();
    std::map<std::string, SDL_Texture*> getTextures() const;

   public:
    std::map<std::string, SDL_Texture*> _textures;
};