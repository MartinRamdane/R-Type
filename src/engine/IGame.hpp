/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

#include "../global/EventHandler.hpp"
#include "../server/ThreadSafeQueue.hpp"
#include "../server/UDPServer.hpp"

class IGame
{
public:
    enum ProjectileGroup
    {
        PLAYER,
        ENEMY,
        BOSS
    };


    virtual ~IGame() = default;
    virtual void update(ThreadSafeQueue<Event> &events, UDPServer *server) = 0;
    virtual bool isReset() = 0;
    virtual void setReset(bool reset) = 0;

protected:
private:
};

#endif /* !IGAME_HPP_ */
