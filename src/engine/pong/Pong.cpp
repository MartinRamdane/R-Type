/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Pong
*/

#include "Pong.hpp"
#include "../Character.hpp"
#include "Ball.hpp"

Pong* Pong::instance = nullptr;

Pong::Pong(std::shared_ptr<Engine>& engine) : _engine(engine) {
  instance = this;
  _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
  _playersGroups = std::make_shared<EntityType<IEntity>>(10);
  _ballsGroups = std::make_shared<EntityType<IEntity>>(30);

  _pongInitializer = std::make_unique<PongInitializer>(this);
  _pongInitializer->loadLevel(1);

  engine->setRelation(_ballsGroups, _playersGroups, Ball::hurtPlayer);
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
  while (!events.empty()) {
    auto event = events.pop_front();
    switch (event.ACTION_NAME) {
      case ACTION::UP:
        if (_players.size() > 0)
          _players[getId(event) - 1]->move(0, -1);
        break;
      case ACTION::DOWN:
        if (_players.size() > 0)
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
  info.speed = 5;
  info.name = "Ball";
  info.assetFile = _assets["Ball"]();
  info.spriteConfigJsonFileName = "pongConfig.json";
  info.spriteConfigJsonObjectName = "Ball";
  info.scaleX = 0.75;
  info.scaleY = 0.75;
  info.x = 425;
  info.y = 239;
  std::shared_ptr<Ball> entity = std::make_shared<Ball>(info);
  balls.push_back(entity);
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
  std::shared_ptr<Character> entity = std::make_shared<Character>(info);
  _players.push_back(entity);
  _playersGroups->insert(entity);
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