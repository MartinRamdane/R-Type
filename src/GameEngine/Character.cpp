/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, float speed, int nbSprite, float fireRate, int life, int damage)
{
    _path = path;
    _x = x;
    _y = y;
    _angle = angle;
    _scaleX = scaleX;
    _scaleY = scaleY;
    _speed = speed;
    _id = id;
    _oldX = x;
    _oldY = y;
    _nbSprite = nbSprite;
    _created = false;
    _isDead = false;
    _fireRate = fireRate;
    _life = life;
    _damage = damage;
    _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
    _lastShootTime = std::chrono::high_resolution_clock::now();
    _currentTime = _lastShootTime;
}

Character::~Character()
{
}

void Character::setPosition(float x, float y)
{
    setOldPosition(_x, _y);
    _x = x;
    _y = y;
}

void Character::setRotation(float angle)
{
    _angle = angle;
}

void Character::move(float x, float y)
{
    setOldPosition(_x, _y);
    _x += x;
    _y += y;
}

void Character::rotate(float angle)
{
    _angle += angle;
}

void Character::update()
{
}

std::tuple<float, float> Character::getPosition() const
{
    return std::make_tuple(_x, _y);
}

float Character::getRotation() const
{
    return _angle;
}

void Character::setScale(float x, float y)
{
    _scaleX = x;
    _scaleY = y;
}

std::tuple<float, float> Character::getScale() const
{
    return std::make_tuple(_scaleX, _scaleY);
}

std::string Character::getPath() const
{
    return _path;
}

void Character::setPath(std::string path)
{
    _path = path;
}

void Character::setSpeed(float speed)
{
    _speed = speed;
}

float Character::getSpeed() const
{
    return _speed;
}

void Character::setOldPosition(float x, float y)
{
    _oldX = x;
    _oldY = y;
}

std::tuple<float, float> Character::getOldPosition() const
{
    return std::make_tuple(_oldX, _oldY);
}

int Character::getId() const
{
    return _id;
}

int Character::getNbSprite() const
{
    return _nbSprite;
}

bool Character::isCreated() const
{
    return _created;
}

void Character::setCreated(bool created)
{
    _created = created;
}

bool Character::isDead() const
{
    return _isDead;
}

void Character::setLife(int life)
{
    _life = life;
}

int Character::getLife() const
{
    return _life;
}

void Character::setDamage(int damage)
{
    _damage = damage;
}

int Character::getDamage() const
{
    return _damage;
}

void Character::setFireRate(int fireRate)
{
    _fireRate = fireRate;
}

int Character::getFireRate() const
{
    return _fireRate;
}

void Character::takeDamage(int damage)
{
    _life -= damage;
    if (_life <= 0)
        _isDead = true;
}

bool Character::canShoot()
{
    _currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = _currentTime - _lastShootTime;

    if (elapsedTime >= _targetFrameDuration)
    {
        _lastShootTime = _currentTime;

        return true;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    return false;
}