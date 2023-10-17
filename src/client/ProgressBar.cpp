/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** ProgressBar.cpp
*/

#include "ProgressBar.hpp"

ProgressBar::ProgressBar()
{
    _progressBarBack.setSize(sf::Vector2f(500, 15));
    _progressBarBack.setFillColor(sf::Color::White);
    _progressBarBack.setPosition(sf::Vector2f(0, 468));
    _progressBar.setSize(sf::Vector2f(500, 5));
    _progressBar.setFillColor(sf::Color::Green);
    _progressBar.setPosition(sf::Vector2f(0, 468));
    _maxProgress = 100;
    _progress = _maxProgress;
}

void ProgressBar::update()
{
    _progressBar.setSize(sf::Vector2f(500 * (_progress / _maxProgress), 10));
}

void ProgressBar::setProgress(float progress)
{
    _progress = progress;
}

void ProgressBar::setMaxProgress(float maxProgress)
{
    _maxProgress = maxProgress;
}

void ProgressBar::draw(sf::RenderWindow &window)
{
    window.draw(_progressBarBack);
    window.draw(_progressBar);
}