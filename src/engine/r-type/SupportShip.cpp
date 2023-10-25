/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** SupportShip
*/

#include "SupportShip.hpp"

SupportShip::SupportShip(EntityInfo info, int relatedPlayerId) : Character(info) {
    JsonParser parser;
    nlohmann::json json = parser.readFile("SupportShip.rType.json");
    setShootAsset(parser.get<std::string>(json, "ProjectileType"));
    setSpeed(RType::instance->getPlayer(relatedPlayerId)->getSpeed());
    setFireRate(parser.get<float>(json, "FireRate"));
    setProjectileSpeed(parser.get<float>(json, "ProjectileSpeed"));
    setDamage(parser.get<int>(json, "Damage"));
    setLife(parser.get<int>(json, "Life"));
    _relatedPlayerId = relatedPlayerId;
}

SupportShip::SupportShip(EntityInfo info) : Character(info) {
    JsonParser parser;
    nlohmann::json json = parser.readFile("SupportShip.rType.json");
    setShootAsset(parser.get<std::string>(json, "ProjectileType"));
    setFireRate(parser.get<float>(json, "FireRate"));
    setSpeed(6);
    setProjectileSpeed(parser.get<float>(json, "ProjectileSpeed"));
    setDamage(parser.get<int>(json, "Damage"));
    setLife(parser.get<int>(json, "Life"));
    _relatedPlayerId = -1;
}

SupportShip::~SupportShip() {}

void SupportShip::update() {
    if (_relatedPlayerId == -1) {
        for (auto& it : RType::instance->getPlayers()) {
            if (it->AEntity::getAlliesTouched() && !it->AEntity::getHasSupport() &&
                AEntity::getAlliesTouched()) {
                _relatedPlayerId = it->getId();
                RType::instance->setPlayerHasSupport(_relatedPlayerId, true);
                break;
            }
        }
        if (_relatedPlayerId == -1)
            return;
    }

    if (_x != _oldX || _y != _oldY) {
        setOldPosition(_x, _y);
    }

    auto player = RType::instance->getPlayer(_relatedPlayerId);
    auto pos = player->getPosition();
    int x = std::get<0>(pos);
    int y = std::get<1>(pos);
    if (player->getAlliesTouched() == true && AEntity::getAlliesTouched() == false) {
        player->setAlliesTouched(false);
        setAlliesTouched(false);
    }

    if (_launched) {
        if (_launchX <= 100 && _x < 830 && x > 10) {
            _direction == IEntity::RIGHT ? move(1, 0) : move(-1, 0);
            _launchX++;
            return;
        } else {
            _launchX = 0;
            _launched = false;
            setAlliesTouched(false);
        }
    }

    shoot();
    bool touched = AEntity::getAlliesTouched();
    IEntity::Direction playerDirection = player->getDirection();

    if (playerDirection == IEntity::LEFT && _direction == IEntity::RIGHT) {
        flip();
    } else if (playerDirection == IEntity::RIGHT && _direction == IEntity::LEFT) {
        flip();
    }

    if (playerDirection == IEntity::LEFT && touched) {
        setPosition(x - player->getRadius() - 10, y);
    } else if (playerDirection == IEntity::RIGHT && touched) {
        setPosition(x + player->getRadius() + 10, y);
    } else {
        if (x == _playerOldX && y == _playerOldY) {
            return;
        } else if (x != _playerOldX && y == _playerOldY) {
            _playerOldX = x;
            setPosition(x, _y);
        } else {
            _playerOldX = x;
            _playerOldY = y;
            if (random == 0)
                y = y - 50;
            else
                y = y + 50;
            setPosition(x, y);
        }
    }
}

void SupportShip::shoot() {
    if (!canShoot())
        return;
    auto pos = getPosition();
    EntityInfo info;
    info.x = std::get<0>(pos) + (_direction == RIGHT ? 30 : -30);
    info.y = std::get<1>(pos) - 2;
    info.name = getShootAsset();
    info.scaleX = 0.25;
    info.scaleY = 0.25;
    info.speed = getProjectileSpeed();
    info.damage = getDamage();
    info.spriteConfigJsonObjectName = getShootAsset();
    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    info.direction = _direction;
    RType::instance->createProjectile(info, _direction == IEntity::LEFT ? true : false,
                                      IGame::ProjectileGroup::SUPPORT);
    info.y = info.y + 4;
    RType::instance->createProjectile(info, _direction == IEntity::LEFT ? true : false,
                                      IGame::ProjectileGroup::SUPPORT);
}

int SupportShip::getRelatedPlayerId() const {
    return _relatedPlayerId;
}

void SupportShip::launch() {
    if (AEntity::getAlliesTouched()) {
        _launched = true;
    }
}
