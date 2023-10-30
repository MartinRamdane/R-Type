#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Camera {
public:
    Camera(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {};
    ~Camera() {};

    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    };

    SDL_Rect apply(const SDL_Rect& rect) const {
        SDL_Rect result = rect;
        result.x -= x;
        result.y -= y;
        return result;
    };

private:
    int x, y, width, height;
};