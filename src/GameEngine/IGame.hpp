/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** IGame
*/

#ifndef IGAME_HPP_
#define IGAME_HPP_

class IGame
{
public:
    enum Event
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        SHOOT,
        QUIT,
        SHIELD,
        UNKNOWN
    };
    virtual ~IGame() = default;

    virtual void update(Event event) = 0;

protected:
private:
};

#endif /* !IGAME_HPP_ */
