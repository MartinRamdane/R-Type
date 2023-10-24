/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Character
*/

#include "Character.hpp"

Character::Character(EntityInfo info) : AEntity(info) {
  _fireRate = 3;
  _lifeValue = 100;
  _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
  _lastShootTime = std::chrono::high_resolution_clock::now();
  _currentTime = _lastShootTime;
}

Character::~Character() {}

void Character::move(float x, float y) {
  if ((_x + x * _speed) > Engine::instance->getWindowWidth() - _radius ||
      (_x + x * _speed) < 0 + _radius ||
      (_y + y * _speed) > Engine::instance->getWindowHeight() - (_radius / 2) ||
      (_y + y * _speed) < 0 + (_radius / 2))
    return;
  setOldPosition(_x, _y);
  _x += x * _speed;
  _y += y * _speed;
}

void Character::setFireRate(float fireRate) {
  _fireRate = fireRate;
  _targetFrameDuration = std::chrono::duration<double>(1.0 / _fireRate);
}

float Character::getFireRate() const {
  return _fireRate;
}

bool Character::canShoot() {
  _currentTime = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedTime = _currentTime - _lastShootTime;

  if (elapsedTime >= _targetFrameDuration) {
    _lastShootTime = _currentTime;

    return true;
  }
  return false;
}

void Character::shoot() {
  if (!canShoot())
    return;
  auto pos = getPosition();
  EntityInfo info;
  info.x = std::get<0>(pos) + (_direction == RIGHT ? 30 : -30);
  info.y = std::get<1>(pos) + 2;
  info.name = getShootAsset();
  info.scaleX = 0.25;
  info.scaleY = 0.25;
  info.speed = getProjectileSpeed();
  info.damage = getDamage();
  info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
  info.spriteConfigJsonObjectName = getShootAsset();
  info.direction = _direction;
  Game::instance->createProjectile(info,
                                   _direction == IEntity::LEFT ? true : false,
                                   IGame::ProjectileGroup::PLAYER);
}

void Character::update() {
  if (_x != _oldX || _y != _oldY)
    setOldPosition(_x, _y);
}

void Character::setShootAsset(std::string shootAsset) {
  _shootAsset = shootAsset;
}

void Character::setMovementType(std::string movementType) {
  _movementType = movementType;
}

std::string Character::getMovementType() const {
  return _movementType;
}

std::string Character::getShootAsset() const {
  return _shootAsset;
}

void Character::setProjectileSpeed(float projectileSpeed) {
  _projectileSpeed = projectileSpeed;
}

float Character::getProjectileSpeed() const {
  return _projectileSpeed;
}

void Character::resetLife() {
  _life = _lifeValue;
}

void Character::setId(int id) {
  _id = id;
}

void Character::setLifeValue(int lifeValue) {
  _lifeValue = lifeValue;
}

void Character::takeDamage(int damage) {
  _life -= damage;
  if (_life <= 0)
    _isDead = true;
}

void Character::hurtEnemy(IEntity& self, IEntity& you) {
  self.takeDamage(you.getDamage());
  you.kill();
  auto pos = you.getPosition();
  Game::instance->createExplosion(std::get<0>(pos), std::get<1>(pos));
}

void Character::alliesTouched(IEntity& self, IEntity& you) {
  self.setAlliesTouched(true);
  you.setAlliesTouched(true);
}
