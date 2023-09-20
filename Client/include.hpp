/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** include.hpp
*/

#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>
// #include <SFML/Audio.hpp>
// #include <SFML/Network.hpp>
#include "Entity.hpp"

#ifndef structure
#define structure

struct Login
{
    std::string name;
    std::string port;
    std::string ip;
};

#endif

struct Login startgame();
std::map<int, Entity> parseMessage(std::string message, std::map<int, Entity> &entities);