/*
** EPITECH PROJECT, 2023
** bs_plazza [WSL: Ubuntu]
** File description:
** Mutex
*/

#ifndef MUTEX_HPP_
#define MUTEX_HPP_
#include "IMutex.hpp"
#include <mutex>
class Mutex : public IMutex
{
public:
    Mutex();
    ~Mutex();
    void lock();
    void unlock();
    bool trylock();

protected:
    std::mutex _mut;

private:
};

#endif /* !MUTEX_HPP_ */