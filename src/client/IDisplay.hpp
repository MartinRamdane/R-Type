/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** IDisplay.hpp
*/

#pragma once

#include <iostream>
#include <map>
#include <memory>
#include "IEntity.hpp"

class UDPClient;

class TCPClientImpl;

class IDisplay {
   public:
    virtual ~IDisplay() = default;

    virtual void createWindow(std::string name, int x, int y) = 0;

    virtual void draw(std::map<int, std::shared_ptr<IEntity>>* _entities) = 0;

    virtual void handleEvent() = 0;

    virtual bool getClosed() const = 0;

    virtual bool windowIsOpen() const = 0;

    virtual void closeWindow() = 0;

    virtual std::shared_ptr<IEntity> createEntity(IEntity::EntityInfos entityInfos) = 0;

    virtual std::vector<std::string> getEvents() = 0;
};