/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RessourceManagerSDL.cpp
*/

#include "RessourceManagerSDL.hpp"

RessourceManagerSDL::RessourceManagerSDL(SDL_Renderer* renderer) {
    std::string directory = "assets";
    for (const auto& entry : std::filesystem::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filePath = entry.path().string();
            std::string key = entry.path().stem().string();
            key = key + ".png";
            SDL_Surface* imageSurface = IMG_Load(filePath.c_str());
            SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
            if (spriteTexture == nullptr) {
                SDL_Log("Failed to load texture %s: %s", key.c_str(), SDL_GetError());
            } else {
                _textures[key] = spriteTexture;
            }
            SDL_FreeSurface(imageSurface);
        }
    }
}

RessourceManagerSDL::~RessourceManagerSDL() {
    _textures.clear();
}

std::map<std::string, SDL_Texture*> RessourceManagerSDL::getTextures() const {
    return _textures;
}