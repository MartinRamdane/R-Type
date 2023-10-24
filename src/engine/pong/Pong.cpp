/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Pong
*/

#include "Pong.hpp"
#include "../Character.hpp"
#include "Ball.hpp"
#include "Player.hpp"

Pong* Pong::instance = nullptr;

Pong::Pong(std::shared_ptr<Engine>& engine) : _engine(engine) {
    instance = this;
    _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
    _playersGroups = std::make_shared<EntityType<IEntity>>(5);
    _ballsGroups = std::make_shared<EntityType<IEntity>>(15);
    _textGroups = std::make_shared<EntityType<IEntity>>(0);

    _pongInitializer = std::make_unique<PongInitializer>(this);
    _pongInitializer->loadLevel(1);

    createScores();
}

Pong::~Pong() {}

int Pong::getId(Event event) {
    std::stringstream ss(event.body);
    std::string playerId;
    ss >> playerId;
    int id = std::stoi(playerId.substr(1));
    return (id);
}

void Pong::update(ThreadSafeQueue<Event>& events) {

    if (_balls.size() > 0) {
        std::tuple<float, float> ballPos = _balls[0]->getPosition();
        float ballX = std::get<0>(ballPos);
        float ballY = std::get<1>(ballPos) - _balls[0]->getRadius() / 2;

        for (auto& player : _players) {
            std::tuple<float, float> playerPos = player->getPosition();
            float playerWidth = player->getWidth();
            float playerHeight = player->getHeight();
            float playerX = std::get<0>(playerPos);
            float playerY = std::get<1>(playerPos) - playerHeight / 2;
            float _radius = _balls[0]->getRadius() * std::get<0>(_balls[0]->getScale());

            if (ballX + _radius > playerX && ballX - _radius < playerX + playerWidth &&
                ballY + _radius > playerY && ballY - _radius < playerY + playerHeight) {
                _balls[0]->hurtPlayer(*_balls[0], *player);
            }
        }
    }

    while (!events.empty()) {
        auto event = events.pop_front();
        switch (event.ACTION_NAME) {
            case ACTION::UP:
                if (_players.size() > 0 && getId(event) - 1 < _players.size())
                    _players[getId(event) - 1]->move(0, -1);
                break;
            case ACTION::DOWN:
                if (_players.size() > 0 && getId(event) - 1 < _players.size())
                    _players[getId(event) - 1]->move(0, 1);
                break;
            case ACTION::READY:
                addPlayer();
                createBall();
                setAllEntitiesToCreated();
                break;
            default:
                break;
        }
    }
    if (_balls.size() > 0) {
        if (_balls[0]->isDead()) {
            float dirX = std::get<0>(_balls[0]->getDirectionVector());
            if (dirX > 0) {
                _scorePlayer1++;
                _texts[0]->setText(std::to_string(_scorePlayer1));
            } else {
                _scorePlayer2++;
                _texts[1]->setText(std::to_string(_scorePlayer2));
            }
            _balls.clear();
            createBall();
        }
    }
}

bool Pong::isReset() {
    return _reset;
}

void Pong::setReset(bool reset) {
    _reset = reset;
}

void Pong::setAllEntitiesToCreated() {
    for (auto& entity : _staticObjects) {
        entity->setCreated(false);
    }
    for (auto& entity : _players) {
        entity->setCreated(false);
    }
    for (auto& entity : _balls) {
        entity->setCreated(false);
    }
    for (auto& entity : _texts) {
        entity->setCreated(false);
    }
}

void Pong::createEntity(IEntity::EntityInfo info) {
    info.id = _lastId++;
    std::shared_ptr<AEntity> entity = std::make_shared<AEntity>(info);
    _staticObjects.push_back(entity);
    _staticObjectsGroups->insert(entity);
}

std::map<std::string, std::function<std::string()>> Pong::getAssets() {
    return _assets;
}

void Pong::createBall() {
    if (_players.size() != 2)
        return;
    IEntity::EntityInfo info;
    info.id = _lastId++;
    info.speed = 8;
    info.name = "Ball";
    info.assetFile = _assets["Ball"]();
    info.spriteConfigJsonFileName = "pongConfig.json";
    info.spriteConfigJsonObjectName = "Ball";
    info.scaleX = 0.75;
    info.scaleY = 0.75;
    info.x = 425;
    info.y = 239;
    std::shared_ptr<Ball> entity = std::make_shared<Ball>(info);
    _balls.push_back(entity);
    _ballsGroups->insert(entity);
}

void Pong::addPlayer() {
    IEntity::EntityInfo info;
    info.id = _lastId++;
    info.speed = 5;
    info.name = "Player";
    info.assetFile = _assets["Player"]();
    info.spriteConfigJsonFileName = "pongConfig.json";
    info.spriteConfigJsonObjectName = "Player";
    info.scaleX = 0.75;
    info.scaleY = 0.75;
    if (_players.size() == 0) {
        info.x = 35;
        info.y = 239;
    } else if (_players.size() == 1) {
        info.x = 815;
        info.y = 239;
    } else
        return;
    std::shared_ptr<Player> entity = std::make_shared<Player>(info);
    _players.push_back(entity);
    _playersGroups->insert(entity);
    entity->setSize(8, 75);
}

void Pong::createScores() {
    IEntity::EntityInfo info;
    info.id = _lastId++;
    info.text = std::to_string(_scorePlayer1);
    info.name = "ScorePlayer1";
    info.x = 212;
    info.y = 50;
    info.scaleX = 30;
    std::shared_ptr<AEntity> entity = std::make_shared<AEntity>(info);
    _texts.push_back(entity);
    _textGroups->insert(entity);
    info.id = _lastId++;
    info.text = std::to_string(_scorePlayer2);
    info.name = "ScorePlayer2";
    info.x = 636;
    info.y = 50;
    info.scaleX = 30;
    std::shared_ptr<AEntity> entity2 = std::make_shared<AEntity>(info);
    _texts.push_back(entity2);
    _textGroups->insert(entity2);
}

std::map<std::string, std::function<std::string()>> Pong::_assets = {
    {"Border",
     []() {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("pongSetup.json"),
                                        "Game.Assets.Images.Border");
     }},
    {"Player",
     []() {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("pongSetup.json"),
                                        "Game.Assets.Images.Player");
     }},
    {"Ball",
     []() {
         JsonParser parser;
         return parser.get<std::string>(JsonParser::readFile("pongSetup.json"),
                                        "Game.Assets.Images.Ball");
     }},
};