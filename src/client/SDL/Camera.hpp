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
        float scaleX = 1920 / width;
        float scaleY = 1080 / height;
        SDL_Rect result = rect;
        result.x = (result.x - x);
        result.y = (result.y - y);
        result.w *= scaleX;
        result.h *= scaleY;
        return result;
    };

private:
    int x, y, width, height;
};