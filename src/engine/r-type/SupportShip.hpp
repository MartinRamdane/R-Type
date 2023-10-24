/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SupportShip
*/

#pragma once

#include "../Character.hpp"
#include <chrono>

class SupportShip : public Character
{
public:
    SupportShip(EntityInfo info, int relatedPlayerId);
    ~SupportShip();
    void shoot() override;
    void update() override;
    int getRelatedPlayerId() const;
    void launch();

protected:
private:
    int _relatedPlayerId;
    int _playerOldX;
    int _playerOldY;
    bool _launched = false;
    int _launchX = 0;
};
