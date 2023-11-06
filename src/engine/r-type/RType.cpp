/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** RType
*/

#include "RType.hpp"
#include "../Protocol.hpp"
#include "Boss.hpp"
#include "Classic.hpp"
#include "Dropper.hpp"
#include "Enemy.hpp"
#include "Shield.hpp"
#include "Shooter.hpp"
#include "Speed.hpp"
#include "SupportShip.hpp"
#include "Tank.hpp"
#include "Wall.hpp"

RType* RType::instance = nullptr;

RType::RType(std::shared_ptr<Engine>& engine) : _engine(engine) {
    createAssetList();
    instance = this;
    // Create all entities groups
    _playersGroups = std::make_shared<EntityType<IEntity>>(16);
    _projectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _enemyProjectilesGroups = std::make_shared<EntityType<IEntity>>(3);
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _orangeRobotGroups = std::make_shared<EntityType<IEntity>>(20);
    _flyerGroups = std::make_shared<EntityType<IEntity>>(10);
    _greenRobotGroups = std::make_shared<EntityType<IEntity>>(24);
    _supportProjectilesGroups = std::make_shared<EntityType<IEntity>>(4);
    _supportShipGroups = std::make_shared<EntityType<IEntity>>(16);
    _dropperGroups = std::make_shared<EntityType<IEntity>>(14);
    _wormGroups = std::make_shared<EntityType<IEntity>>(16);
    _bossGroups = std::make_shared<EntityType<IEntity>>(94);
    _bombermanGroups = std::make_shared<EntityType<IEntity>>(10);
    _bombGroups = std::make_shared<EntityType<IEntity>>(4);
    _circularRobotGroups = std::make_shared<EntityType<IEntity>>(15);
    _wallGroups = std::make_shared<EntityType<IEntity>>(30);

    // initializeLevel
    _levelInitializer = std::make_unique<LevelInitializer>(this);
    _levelInitializer->loadLevel(_currentLevel);

    // Add collision between entities groups
    _engine->setRelation(_projectilesGroups, _orangeRobotGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _flyerGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _playersGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _greenRobotGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _dropperGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _wormGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _bossGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _bombermanGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _bombGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _circularRobotGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_projectilesGroups, _wallGroups,
                         Projectile::hurtEntity);

    _engine->setRelation(_enemyProjectilesGroups, _playersGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _flyerGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _playersGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _orangeRobotGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _dropperGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _bossGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _bombermanGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _bombGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _dropperGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _circularRobotGroups,
                         Projectile::hurtEntity);
    _engine->setRelation(_supportProjectilesGroups, _wallGroups,
                         Projectile::hurtEntity);

    _engine->setRelation(_playersGroups, _orangeRobotGroups,
                         Character::hurtEntities);
    _engine->setRelation(_playersGroups, _flyerGroups, Character::hurtEntities);
    _engine->setRelation(_playersGroups, _greenRobotGroups,
                         Character::hurtEntities);
    _engine->setRelation(_playersGroups, _wormGroups, Character::hurtEntities);
    _engine->setRelation(_playersGroups, _bossGroups, Character::hurtEntities);
    _engine->setRelation(_playersGroups, _bombermanGroups,
                         Character::hurtEntities);
    _engine->setRelation(_playersGroups, _bombGroups, Character::hurtEntities);
    _engine->setRelation(_playersGroups, _circularRobotGroups,
                         Character::hurtEntities);

    _engine->setRelation(_playersGroups, _supportShipGroups,
                         Character::entitiesCollision);
    _engine->setRelation(_orangeRobotGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_flyerGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_wormGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_bossGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_greenRobotGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_bombermanGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_bombGroups, _supportShipGroups,
                         Character::hurtFirstEntity);
    _engine->setRelation(_circularRobotGroups, _supportShipGroups,
                         Character::hurtFirstEntity);

    _engine->setRelation(_playersGroups, _wallGroups,
                         Character::hurtFirstEntity);
}

RType::~RType() {
    // Destroy all entities
    std::cout << "starting clearing " << std::endl;
    _players.clear();
    _enemies.clear();
    _projectiles.clear();
    _staticObjects.clear();
    _supportShips.clear();
    _dropper.clear();
    _assets.clear();
    _musics.clear();
    _wall.clear();
    instance = nullptr;
}

void RType::createAssetList() {
    JsonParser parser;
    auto val = JsonParser::readFile("rTypeSetup.json");
    _assets["Classic"] =
        parser.get<std::string>(val, "Game.Assets.Images.Classic");
    _assets["Speed"] = parser.get<std::string>(val, "Game.Assets.Images.Speed");
    _assets["Shooter"] =
        parser.get<std::string>(val, "Game.Assets.Images.Shooter");
    _assets["Tank"] = parser.get<std::string>(val, "Game.Assets.Images.Tank");
    _assets["ShieldSpaceship"] =
        parser.get<std::string>(val, "Game.Assets.Images.ShieldSpaceship");
    _assets["OrangeRobot"] =
        parser.get<std::string>(val, "Game.Assets.Images.OrangeRobot");
    _assets["GreenRobot"] =
        parser.get<std::string>(val, "Game.Assets.Images.GreenRobot");
    _assets["Background"] =
        parser.get<std::string>(val, "Game.Assets.Images.Background");
    _assets["ExplosionSpaceship"] =
        parser.get<std::string>(val, "Game.Assets.Images.ExplosionSpaceShip");
    _assets["Shield"] =
        parser.get<std::string>(val, "Game.Assets.Images.Shield");
    _assets["PlayerProjectile"] =
        parser.get<std::string>(val, "Game.Assets.Images.PlayerProjectile");
    _assets["DiskProjectile"] =
        parser.get<std::string>(val, "Game.Assets.Images.DiskProjectile");
    _assets["OrangeProjectile"] =
        parser.get<std::string>(val, "Game.Assets.Images.OrangeProjectile");
    _assets["Flyer"] = parser.get<std::string>(val, "Game.Assets.Images.Flyer");
    _assets["SupportShip"] =
        parser.get<std::string>(val, "Game.Assets.Images.SupportShip");
    _assets["Dropper"] =
        parser.get<std::string>(val, "Game.Assets.Images.Dropper");
    _assets["Worm"] = parser.get<std::string>(val, "Game.Assets.Images.Worm");
    _assets["Boss1"] = parser.get<std::string>(val, "Game.Assets.Images.Boss1");
    _assets["Boss1Projectile"] =
        parser.get<std::string>(val, "Game.Assets.Images.Boss1Projectile");
    _assets["Bomberman"] =
        parser.get<std::string>(val, "Game.Assets.Images.Bomberman");
    _assets["Bomb"] = parser.get<std::string>(val, "Game.Assets.Images.Bomb");
    _assets["CircularRobot"] =
        parser.get<std::string>(val, "Game.Assets.Images.CircularRobot");
    _assets["Wall1"] = parser.get<std::string>(val, "Game.Assets.Images.Wall1");
    _assets["Wall2"] = parser.get<std::string>(val, "Game.Assets.Images.Wall2");
    _assets["Wall3"] = parser.get<std::string>(val, "Game.Assets.Images.Wall3");
    _assets["Boss2"] = parser.get<std::string>(val, "Game.Assets.Images.Boss2");
    _assets["Boss2Projectile"] =
        parser.get<std::string>(val, "Game.Assets.Images.Boss2Projectile");
}

int RType::getId(Event event) {
    std::stringstream ss(event.body);
    std::string playerId;
    ss >> playerId;
    int id = std::stoi(playerId.substr(1));
    return (id);
}

std::shared_ptr<Character> RType::getRandomSpaceship() {
    srand(time(NULL));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 4);
    int random = distrib(gen);
    IEntity::EntityInfo info;

    info.x = 50;
    int randomY = rand() % 4;
    info.y = 100 + randomY * 20;

    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    info.spriteConfigJsonObjectName = "Spaceship";
    info.id = _lastId;
    _lastId++;

    switch (random) {
        case 0:
            info.assetFile = _assets["Classic"];
            return (std::make_shared<Classic>(info));
        case 1:
            info.assetFile = _assets["Speed"];
            return (std::make_shared<Speed>(info));
        case 2:
            info.assetFile = _assets["Shooter"];
            return (std::make_shared<Shooter>(info));
        case 3:
            info.assetFile = _assets["Tank"];
            return (std::make_shared<Tank>(info));
        case 4:
            info.assetFile = _assets["ShieldSpaceship"];
            return (std::make_shared<Shield>(info));
        default:
            info.assetFile = _assets["Classic"];
            return (std::make_shared<Classic>(info));
    }
}

void RType::update(ThreadSafeQueue<Event>& events) {
    eraseDeadEntity();
    std::string key = "";
    while (!events.empty()) {
        auto event = events.pop_front();
        switch (event.ACTION_NAME) {
            case ACTION::LEFT:
                if (!_players.empty() && (int)_players.size() >= getId(event))
                    _players[getId(event) - 1]->move(-1, 0);
                break;
            case ACTION::RIGHT:
                if (!_players.empty() && (int)_players.size() >= getId(event))
                    _players[getId(event) - 1]->move(1, 0);
                break;
            case ACTION::UP:
                if (!_players.empty() && (int)_players.size() >= getId(event))
                    _players[getId(event) - 1]->move(0, -1);
                break;
            case ACTION::DOWN:
                if (!_players.empty() && (int)_players.size() >= getId(event))
                    _players[getId(event) - 1]->move(0, 1);
                break;
            case ACTION::SPACE:
                if (!_players.empty() && (int)_players.size() >= getId(event))
                    _players[getId(event) - 1]->shoot();
                break;
            case ACTION::FLIP:
                if (!_players.empty() && (int)_players.size() >= getId(event))
                    _players[getId(event) - 1]->flip();
                break;
            case ACTION::READY:
                _players.push_back(getRandomSpaceship());
                _playersGroups->insert(_players[_players.size() - 1]);
                setAllEntitiesToCreated();
                break;
            case ACTION::KEY:
                key = Protocol::getKeyFromBody(event.body);
                if (key == "s") {
                    if (!_players.empty() &&
                        (int)_players.size() >=
                            Protocol::getIdFromBodyKey(event.body))
                        _players[Protocol::getIdFromBodyKey(event.body) - 1]
                            ->action();
                }
                if (key == "l") {
                    for (auto supportShip : _supportShips) {
                        if (supportShip->getRelatedPlayerId() ==
                            _players[Protocol::getIdFromBodyKey(event.body) - 1]
                                ->getId()) {
                            supportShip->launch();
                            break;
                        }
                    }
                }
                if (key == "c") {
                    for (auto supportShip : _supportShips) {
                        if (supportShip->getRelatedPlayerId() ==
                            _players[Protocol::getIdFromBodyKey(event.body) - 1]
                                ->getId()) {
                            supportShip->setEntitiesHasCollided(true);
                            _players[Protocol::getIdFromBodyKey(event.body) - 1]
                                ->setEntitiesHasCollided(true);
                            break;
                        }
                    }
                }
                break;
            case ACTION::DEAD: {
                int id = std::stoi(event.body);
                eraseDeadEntity(id);
                break;
            }
            default:
                break;
        }
    }
    if (_enemies.size() == 0 && _currentLevel != _maxLevel) {
        _lastId = _players.size() - 1;
        _currentLevel++;
        deleteAllEntities();
        _reset = true;
        _levelInitializer->loadLevel(_currentLevel);
        for (auto player : _players) {
            for (auto player : _players) {
                int randomY = rand() % 4;
                int y = 100 + randomY * 20;
                player->resetLife();
                player->setCreated(false);
                player->setEntitiesHasCollided(false);
                player->setHasSupport(false);
                player->setDirection(IEntity::Direction::RIGHT);
                player->setPosition(50, y);
            }
        }
    }
}

void RType::createExplosion(int x, int y) {
    IEntity::EntityInfo info;
    info.x = x;
    info.y = y;
    info.assetFile = _assets["ExplosionSpaceship"];
    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    info.spriteConfigJsonObjectName = "ExplosionSpaceship";
    info.scaleX = 2;
    info.scaleY = 2;
    info.id = _lastId;
    _lastId++;
    std::shared_ptr<AEntity> explosion = std::make_shared<AEntity>(info);
    _staticObjectsGroups->insert(explosion);
    _staticObjects.push_back(explosion);
}

void RType::createProjectile(IEntity::EntityInfo info, bool flip,
                             IGame::ProjectileGroup group) {
    info.assetFile = _assets[info.name];
    info.id = _lastId;
    _lastId++;
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>(info);
    if (group == ProjectileGroup::PLAYER) {
        _projectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    } else if (group == ProjectileGroup::ENEMY ||
               group == ProjectileGroup::BOSS) {
        if (info.name == "Bomb" || info.name == "Boss2Projectile")
            _bombGroups->insert(projectile);
        else
            _enemyProjectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    } else if (group == ProjectileGroup::SUPPORT) {
        _supportProjectilesGroups->insert(projectile);
        _projectiles.push_back(projectile);
    }
    if (flip)
        projectile->setFlip(flip);
}

std::shared_ptr<AEntity> RType::createShield(int x, int y, float speed) {
    IEntity::EntityInfo info;
    info.x = x;
    info.y = y;
    info.assetFile = _assets["Shield"];
    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    info.spriteConfigJsonObjectName = "Shield";
    info.id = _lastId;
    info.speed = speed;
    _lastId++;
    std::shared_ptr<AEntity> _shield = std::make_shared<AEntity>(info);
    _staticObjectsGroups->insert(_shield);
    _staticObjects.push_back(_shield);
    return (_shield);
}

void RType::createDropper(IEntity::EntityInfo info) {
    std::shared_ptr<Dropper> dropper = std::make_shared<Dropper>(info);
    _dropperGroups->insert(dropper);
    _dropper.push_back(dropper);
}

std::shared_ptr<AEntity> RType::createSupportShip(int x, int y) {
    IEntity::EntityInfo info;
    info.x = x;
    info.y = y;
    info.assetFile = _assets["SupportShip"];
    info.spriteConfigJsonFileName = "rTypeAnimationConfig.json";
    info.spriteConfigJsonObjectName = "SupportShip";
    info.scaleX = 0.7;
    info.scaleY = 0.7;
    info.id = _lastId;
    _lastId++;
    std::shared_ptr<SupportShip> support = std::make_shared<SupportShip>(info);
    _supportShipGroups->insert(support);
    _supportShips.push_back(support);
    return (support);
}

void RType::eraseDeadEntity(int id) {
    for (auto it = _staticObjects.begin(); it != _staticObjects.end(); it++) {
        if ((*it)->getId() == id) {
            (*it)->kill();
            _staticObjects.erase(it);
            break;
        }
    }
}

void RType::eraseDeadEntity() {
    for (auto it = _staticObjects.begin(); it != _staticObjects.end(); it++) {
        if ((*it)->isSound()) {
            (*it)->kill();
        }
        if ((*it)->isDead()) {
            _staticObjects.erase(it);
            break;
        }
    }
    for (auto it = _enemies.begin(); it != _enemies.end(); it++) {
        if ((*it)->isDead()) {
            _enemies.erase(it);
            break;
        }
    }
    for (auto it = _players.begin(); it != _players.end(); it++) {
        if ((*it)->isDead()) {
            if ((*it)->getHasSupport()) {
                for (auto supportShip : _supportShips) {
                    if (supportShip->getRelatedPlayerId() == (*it)->getId()) {
                        supportShip->kill();
                        break;
                    }
                }
            }
            _players.erase(it);
            break;
        }
    }
    for (auto it = _projectiles.begin(); it != _projectiles.end(); it++) {
        if ((*it)->isDead()) {
            _projectiles.erase(it);
            break;
        }
    }
    for (auto it = _supportShips.begin(); it != _supportShips.end(); it++) {
        if ((*it)->isDead()) {
            _supportShips.erase(it);
            break;
        }
    }
    for (auto it = _dropper.begin(); it != _dropper.end(); it++) {
        if ((*it)->isDead()) {
            _dropper.erase(it);
            break;
        }
    }
    for (auto it = _musics.begin(); it != _musics.end(); it++) {
        if ((*it)->isSound()) {
            (*it)->kill();
        }
        if ((*it)->isDead()) {
            _musics.erase(it);
            break;
        }
    }
    for (auto it = _wall.begin(); it != _wall.end(); it++) {
        if ((*it)->isDead()) {
            _wall.erase(it);
            break;
        }
    }
}

void RType::setAllEntitiesToCreated() {
    for (auto staticObject : _staticObjects) {
        staticObject->setCreated(false);
    }
    for (auto enemy : _enemies) {
        enemy->setCreated(false);
    }
    for (auto player : _players) {
        player->setCreated(false);
    }
    for (auto projectile : _projectiles) {
        projectile->setCreated(false);
    }
    for (auto supportShip : _supportShips) {
        supportShip->setCreated(false);
    }
    for (auto dropper : _dropper) {
        dropper->setCreated(false);
    }
    for (auto music : _musics) {
        music->setCreated(false);
    }
    for (auto wall : _wall) {
        wall->setCreated(false);
    }
}

void RType::deleteAllEntities() {
    for (auto staticObject : _staticObjects)
        staticObject->kill();
    for (auto enemy : _enemies)
        enemy->kill();
    for (auto projectile : _projectiles)
        projectile->kill();
    for (auto supportShip : _supportShips)
        supportShip->kill();
    for (auto dropper : _dropper)
        dropper->kill();
    for (auto music : _musics)
        music->kill();
    _staticObjects.clear();
    _enemies.clear();
    _projectiles.clear();
    _supportShips.clear();
    _dropper.clear();
    _wall.clear();
    _staticObjectsGroups->clear();
    _greenRobotGroups->clear();
    _flyerGroups->clear();
    _orangeRobotGroups->clear();
    _projectilesGroups->clear();
    _circularRobotGroups->clear();
    _enemyProjectilesGroups->clear();
    _supportProjectilesGroups->clear();
    _supportShipGroups->clear();
    _dropperGroups->clear();
    _wormGroups->clear();
    _bossGroups->clear();
    _bombermanGroups->clear();
    _bombGroups->clear();
    _wallGroups->clear();
    _musics.clear();
}

bool RType::isReset() {
    return (_reset);
}

void RType::setReset(bool reset) {
    _reset = reset;
}

int RType::getCurrentId() {
    return (_lastId);
}

int RType::getCurrentLevel() {
    return (_currentLevel);
}

std::map<std::string, std::string> RType::getAssets() {
    return (_assets);
}

void RType::setCurrentId(int id) {
    _lastId = id;
}

void RType::createBoss(IEntity::EntityInfo info) {
    std::shared_ptr<Boss> enemy = std::make_shared<Boss>(info);
    _enemies.push_back(enemy);
    _bossGroups->insert(enemy);
}

void RType::createEnemy(IEntity::EntityInfo info) {
    std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(info);
    _enemies.push_back(enemy);
    if (info.name == "OrangeRobot")
        _orangeRobotGroups->insert(enemy);
    else if (info.name == "Flyer")
        _flyerGroups->insert(enemy);
    else if (info.name == "GreenRobot")
        _greenRobotGroups->insert(enemy);
    else if (info.name == "Worm")
        _wormGroups->insert(enemy);
    else if (info.name == "Bomberman")
        _bombermanGroups->insert(enemy);
    else if (info.name == "CircularRobot")
        _circularRobotGroups->insert(enemy);
}

void RType::createBackground(IEntity::EntityInfo info) {
    std::shared_ptr<AEntity> background = std::make_shared<AEntity>(info);
    _staticObjects.push_back(background);
    _staticObjectsGroups->insert(background);
}

void RType::createWall(IEntity::EntityInfo info) {
    std::shared_ptr<Wall> wall = std::make_shared<Wall>(info);
    _wall.push_back(wall);
    _wallGroups->insert(wall);
}

void RType::clearLevel() {
    for (auto player : _players) {
        player->setId(_lastId++);
        player->setCreated(false);
        player->resetLife();
    }
    _orangeRobotGroups->clear();
    _flyerGroups->clear();
    _greenRobotGroups->clear();
    _projectilesGroups->clear();
    _enemyProjectilesGroups->clear();
    _staticObjectsGroups->clear();
    _supportProjectilesGroups->clear();
    _circularRobotGroups->clear();
    _supportShipGroups->clear();
    _dropperGroups->clear();
    _bossGroups->clear();
    _bombermanGroups->clear();
    _wormGroups->clear();
    _bombGroups->clear();
    _wallGroups->clear();
    _enemies.clear();
    _projectiles.clear();
    _staticObjects.clear();
    _supportShips.clear();
    _dropper.clear();
}

std::shared_ptr<AEntity> RType::getPlayer(int id) {
    for (auto player : _players)
        if (player->getId() == id)
            return (player);
    return (NULL);
}

std::vector<std::shared_ptr<AEntity>> RType::getPlayers() {
    std::vector<std::shared_ptr<AEntity>> players;
    for (auto player : _players)
        players.push_back(player);
    return (players);
}

void RType::setPlayerHasSupport(int id, bool support) {
    for (auto player : _players) {
        if (player->getId() == id) {
            player->setHasSupport(support);
            break;
        }
    }
}

std::vector<std::shared_ptr<AEntity>> RType::getEnemies() {
    std::vector<std::shared_ptr<AEntity>> enemies;
    for (auto enemy : _enemies)
        enemies.push_back(enemy);
    return (enemies);
}

void RType::createSound(std::string path) {
    IEntity::EntityInfo info;
    info.assetFile = path;
    info.id = _lastId++;
    std::shared_ptr<AEntity> sound = std::make_shared<AEntity>(info);
    sound->setSound(true);
    _staticObjects.push_back(sound);
    _staticObjectsGroups->insert(sound);
}

void RType::createMusic(std::string path) {
    IEntity::EntityInfo info;
    info.assetFile = path;
    info.id = _lastId++;
    std::shared_ptr<AEntity> music = std::make_shared<AEntity>(info);
    music->setSound(true);
    _musics.push_back(music);
    _staticObjectsGroups->insert(music);
}
