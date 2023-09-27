/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(std::string path, float x, float y, int id, float angle, float scaleX, float scaleY, int nbSprite, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName)
{
    _path = path;
    _x = x;
    _y = y;
    _angle = angle;
    _scaleX = scaleX;
    _scaleY = scaleY;
    _speed = 3;
    _id = id;
    _oldX = x;
    _oldY = y;
    _nbSprite = nbSprite;
    _created = false;
    _isDead = false;
    _fireRate = 3;
    _life = 100;
    _damage = 10;
    _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
    _lastShootTime = std::chrono::high_resolution_clock::now();
    _currentTime = _lastShootTime;
    _spriteConfigJsonPath = spriteConfigJsonPath;
    _spriteConfigJsonObjectName = spriteConfigJsonObjectName;
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
    _x += x * _speed;
    _y += y * _speed;
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

void Character::setFireRate(float fireRate)
{
    _fireRate = fireRate;
    _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
}

float Character::getFireRate() const
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

void Character::hurtProjectile(IEntity &self, IEntity &you)
{
    auto pos = self.getPosition();
    Game::instance->createExplosion(std::get<0>(pos), std::get<1>(pos));
}

void Character::shoot()
{
    if (!canShoot())
        return;
    auto pos = getPosition();
    Game::instance->createProjectile(std::get<0>(pos) + 33, std::get<1>(pos) + 2, _shootAsset, 0.25, 0.25, 5, getDamage(), _shootAsset);
}

std::string Character::getSpriteConfigJsonPath() const
{
    return _spriteConfigJsonPath;
}

std::string Character::getSpriteConfigJsonObjectName() const
{
    return _spriteConfigJsonObjectName;
}

void Character::kill()
{
    _isDead = true;
}

void Character::setShootAsset(std::string shootAsset)
{
    _shootAsset = shootAsset;
}
