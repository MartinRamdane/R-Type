/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Pong
*/

#pragma once

#include "../Engine.hpp"
#include "../IEntity.hpp"
#include "../AEntity.hpp"
#include "../IGame.hpp"
#include <memory>
#include <iostream>

class Pong : public IGame {
 public:
  Pong(std::shared_ptr<Engine>& engine);
  ~Pong();
  static Pong* instance;

  void update(ThreadSafeQueue<Event>& events);
  bool isReset();
  void setReset(bool reset);
  void setAllEntitiesToCreated();

 private:
  std::shared_ptr<Engine> _engine;
  bool _reset = false;
  int _lastId = 0;
  std::vector<std::shared_ptr<AEntity>> _staticObjects;
  std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
  static std::map<std::string, std::function<std::string()>> _assets;
};