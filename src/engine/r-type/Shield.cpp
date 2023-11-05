/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Shield
*/

#include "Shield.hpp"

Shield::Shield(EntityInfo info) : Character(info) {
    // set special attributes
    setLife(70);
    setLifeValue(70);
    _shieldIsUp = false;
    _canActivateShield = true;
    _targetShieldDuration = std::chrono::seconds(5);
    _reloadShieldDuration = std::chrono::seconds(15);
    _shieldStart = std::chrono::high_resolution_clock::now();
    _shield = nullptr;
    setSpeed(3);
}

Shield::~Shield() {}

void Shield::activateShield() {
    if (!_canActivateShield || _shieldIsUp)
        return;
    _shieldIsUp = true;
    _shieldStart = std::chrono::high_resolution_clock::now();
    auto pos = getPosition();
    _shield = RType::instance->createShield(std::get<0>(pos), std::get<1>(pos),
                                            _speed);
}

void Shield::deactivateShield() {
    _shieldIsUp = false;
    _canActivateShield = false;
    _shield->kill();
}

bool Shield::isShieldUp() const {
    return _shieldIsUp;
}

bool Shield::canActivateShield() const {
    return _canActivateShield;
}

void Shield::takeDamage(int damage) {
    if (_shieldIsUp)
        return;
    AEntity::takeDamage(damage);
}

void Shield::update() {
    std::tuple<float, float> pos = getPosition();
    std::tuple<float, float> oldPos = getOldPosition();
    if (std::get<0>(pos) != std::get<0>(oldPos) ||
        std::get<1>(pos) != std::get<1>(oldPos)) {
        setOldPosition(std::get<0>(pos), std::get<1>(pos));
    }
    if (_shieldIsUp) {
        auto pos = getPosition();
        if (pos != _shield->getPosition()) {
            _shield->setPosition(std::get<0>(pos), std::get<1>(pos));
            _shield->setLastMove(true);
        }
        auto _curentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = _curentTime - _shieldStart;
        if (elapsedTime >= _targetShieldDuration) {
            deactivateShield();
            _shieldStart = _curentTime;
        }
    } else {
        auto _curentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = _curentTime - _shieldStart;
        if (elapsedTime >= _reloadShieldDuration) {
            _canActivateShield = true;
            _shieldStart = _curentTime;
        }
    }
}

void Shield::action() {
    activateShield();
}