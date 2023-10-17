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
class IGame
{
public:
    virtual ~IGame() = default;

    virtual void update(ThreadSafeQueue<Event> &events) = 0;
    virtual bool isReset() = 0;
    virtual void setReset(bool reset) = 0;

protected:
private:
};

#endif /* !IGAME_HPP_ */
