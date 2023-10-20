/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(std::string path, float x, float y, int id, float scaleX, float scaleY, std::string spriteConfigJsonPath, std::string spriteConfigJsonObjectName) : AEntity(path, x, y, id, spriteConfigJsonPath, spriteConfigJsonObjectName, scaleX, scaleY)
{
    _fireRate = 3;
    _lifeValue = 100;
    _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
    _lastShootTime = std::chrono::high_resolution_clock::now();
    _currentTime = _lastShootTime;
}

Character::~Character()
{
}

void Character::move(float x, float y)
{
    if ((_x + x * _speed) > Engine::instance->getWindowWidth() - _radius || (_x + x * _speed) < 0 + _radius || (_y + y * _speed) > Engine::instance->getWindowHeight() - (_radius / 2) || (_y + y * _speed) < 0 + (_radius / 2))
        return;
    setOldPosition(_x, _y);
    _x += x * _speed;
    _y += y * _speed;
}

void Character::setFireRate(float fireRate)
{
    std::cout << "Fire rate: " << fireRate << std::endl;
    _fireRate = fireRate;
    _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
    std::cout << "Target frame duration: " << _targetFrameDuration.count() << std::endl;
}

float Character::getFireRate() const
{
    return _fireRate;
}

bool Character::canShoot()
{
    _currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = _currentTime - _lastShootTime;
    // std::cout << elapsedTime.count() << std::endl;
    // std::cout << std::endl;
    // std::cout << _targetFrameDuration.count() << std::endl;
    if (elapsedTime >= _targetFrameDuration)
    {
        _lastShootTime = _currentTime;

        return true;
    }
    return false;
}

void Character::shoot()
{
    if (!canShoot())
        return;
    auto pos = getPosition();
    Game::instance->createProjectile(std::get<0>(pos) + (_direction == RIGHT ? 30 : -30), std::get<1>(pos) + 2, _shootAsset, 0.25, 0.25, getProjectileSpeed(), getDamage(), _shootAsset, "_projectilesGroups", _direction == IEntity::LEFT ? true : false, _direction);
}

void Character::update()
{
    if (_x != _oldX || _y != _oldY)
        setOldPosition(_x, _y);
}

void Character::setShootAsset(std::string shootAsset)
{
    _shootAsset = shootAsset;
}

void Character::setMovementType(std::string movementType)
{
    _movementType = movementType;
}

std::string Character::getMovementType() const
{
    return _movementType;
}

std::string Character::getShootAsset() const
{
    return _shootAsset;
}

void Character::setProjectileSpeed(float projectileSpeed)
{
    _projectileSpeed = projectileSpeed;
}

float Character::getProjectileSpeed() const
{
    return _projectileSpeed;
}

void Character::resetLife()
{
    _life = _lifeValue;
}

void Character::setId(int id)
{
    _id = id;
}

void Character::setLifeValue(int lifeValue)
{
    _lifeValue = lifeValue;
}

void Character::takeDamage(int damage)
{
    _life -= damage;
    if (_life <= 0)
        _isDead = true;
}
