/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate, int nbSprite)
    : Character(path, x, y, id, angle, scaleX, scaleY, speed, nbSprite, fireRate, life, damage)
{
}

Player::~Player()
{
}

void Player::hurtProjectile(IEntity &self, IEntity &you)
{
    auto pos = self.getPosition();
    Game::instance->createExplosion(std::get<0>(pos), std::get<1>(pos));
}

void Player::shoot()
{
    if (!canShoot())
        return;
    auto pos = getPosition();
    Game::instance->createProjectile(std::get<0>(pos) + 33, std::get<1>(pos) + 2, "shoot_type_right6.png", 0.25, 0.25, 5, getDamage());
}