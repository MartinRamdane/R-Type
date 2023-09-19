/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(std::string path, float x, float y, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate)
    : Character(path, x, y, angle, scaleX, scaleY, speed)
{
    _life = life;
    _damage = damage;
    _fireRate = fireRate;
}

Player::~Player()
{
}

void Player::setLife(int life)
{
    _life = life;
}

int Player::getLife() const
{
    return _life;
}

void Player::setDamage(int damage)
{
    _damage = damage;
}

int Player::getDamage() const
{
    return _damage;
}

void Player::setFireRate(int fireRate)
{
    _fireRate = fireRate;
}

int Player::getFireRate() const
{
    return _fireRate;
}
