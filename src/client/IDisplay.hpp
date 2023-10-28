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
    virtual void animate(std::map<int, std::shared_ptr<IEntity>>* _entities) = 0;
    virtual void draw(std::map<int, std::shared_ptr<IEntity>>* _entities) = 0;
    virtual void handleEvent(std::shared_ptr<UDPClient> _udpClient,
                             std::shared_ptr<TCPClientImpl> _client) = 0;
    virtual void update(std::map<int, std::shared_ptr<IEntity>>* _entities,
                        std::shared_ptr<UDPClient> _udpClient) = 0;
    virtual void setPlayerId(int id) = 0;
    virtual int getPlayerId() const = 0;
    virtual bool getClosed() const = 0;
    virtual bool windowIsOpen() const = 0;
    virtual std::shared_ptr<IEntity> createEntity(IEntity::EntityInfos entityInfos) = 0;
};