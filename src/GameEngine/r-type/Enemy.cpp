/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

Enemy::Enemy(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int life, float speed, int damage, int fireRate, int nbSprite)
    : Character(path, x, y, id, angle, scaleX, scaleY, speed, nbSprite, fireRate, life, damage)
{
}

Enemy::~Enemy()
{
}
