/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** DisplaySDL.cpp
*/

#include "DisplaySDL.hpp"

DisplaySDL::DisplaySDL()
{
  SDL_Init(SDL_INIT_VIDEO);
}

DisplaySDL::~DisplaySDL()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void DisplaySDL::createWindow(std::string name, int x, int y)
{
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, x, y, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

