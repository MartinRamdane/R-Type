/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Pong
*/

#include "Pong.hpp"

Pong* Pong::instance = nullptr;

Pong::Pong(std::shared_ptr<Engine>& engine) : _engine(engine) {
  instance = this;
  _staticObjectsGroups = std::make_shared<EntityType<IEntity>>(0);
  IEntity::EntityInfo info;
  info.x = 0;
  info.y = 0;
  info.assetFile = _assets["Border"]();
  info.spriteConfigJsonFileName = "pongConfig.json";
  info.spriteConfigJsonObjectName = "Border";
  info.id = _lastId++;
  std::shared_ptr<AEntity> border = std::make_shared<AEntity>(info);
  _staticObjects.push_back(border);
  _staticObjectsGroups->insert(border);
}

Pong::~Pong() {}

void Pong::update(ThreadSafeQueue<Event>& events) {
  while (!events.empty()) {
    auto event = events.pop_front();
    switch (event.ACTION_NAME) {
      case ACTION::READY:
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

std::map<std::string, std::function<std::string()>> Pong::_assets = {
    {"Border",
     []() {
       JsonParser parser;
       return parser.get<std::string>(JsonParser::readFile("pongSetup.json"),
                                      "Game.Assets.Images.Border");
     }},
};