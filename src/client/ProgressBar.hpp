/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** ProgressBar.hpp
*/

#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <memory>
#include <string>

class ProgressBar {
   public:
    ProgressBar();
    ~ProgressBar(){};
    void update();
    void setProgress(float progress);
    void setMaxProgress(float maxProgress);
    void draw(sf::RenderWindow& window);
    float getProgress() { return _progress; }
    float getMaxProgress() { return _maxProgress; }

   private:
    sf::RectangleShape _progressBar;
    sf::RectangleShape _progressBarBack;
    sf::Vector2f _pos;
    sf::Vector2f _size;
    float _progress;
    float _maxProgress;
};