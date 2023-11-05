/*
 ** EPITECH PROJECT, 2023
 ** bs_plazza [WSL: Ubuntu]
 ** File description:
 ** Mutex
 */

#include "Mutex.hpp"

Mutex::Mutex() {}

Mutex::~Mutex() {}

void Mutex::lock() {
    _mut.lock();
}

void Mutex::unlock() {
    _mut.unlock();
}

bool Mutex::trylock() {
    return _mut.try_lock();
}