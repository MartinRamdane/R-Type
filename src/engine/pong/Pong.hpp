/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Pong
*/

#pragma once

#include <iostream>
#include <memory>
#include "../AEntity.hpp"
#include "../Engine.hpp"
#include "../IEntity.hpp"
#include "../IGame.hpp"
#include "PongInitializer.hpp"
#include <sstream>

class Player;
class Ball;

class Pong : public IGame {
 public:
  Pong(std::shared_ptr<Engine>& engine);
  ~Pong();
  static Pong* instance;

  void update(ThreadSafeQueue<Event>& events);
  bool isReset();
  void setReset(bool reset);
  void setAllEntitiesToCreated();
  void createEntity(IEntity::EntityInfo info);
  std::map<std::string, std::function<std::string()>> getAssets();
  void addPlayer();
  int getId(Event event);
  void createBall();
  void createScores();

 private:
  std::shared_ptr<Engine> _engine;
  bool _reset = false;
  int _lastId = 0;
  std::vector<std::shared_ptr<AEntity>> _staticObjects;
  std::shared_ptr<EntityType<IEntity>> _staticObjectsGroups;
  std::vector<std::shared_ptr<Player>> _players;
  std::shared_ptr<EntityType<IEntity>> _playersGroups;
  std::vector<std::shared_ptr<Ball>> _balls;
  std::shared_ptr<EntityType<IEntity>> _ballsGroups;
  std::vector<std::shared_ptr<AEntity>> _texts;
  std::shared_ptr<EntityType<IEntity>> _textGroups;
  static std::map<std::string, std::function<std::string()>> _assets;
  std::unique_ptr<PongInitializer> _pongInitializer;
  int _scorePlayer1 = 0;
  int _scorePlayer2 = 0;
  std::tuple<float, float> _defaultPlayer1Pos;
  std::tuple<float, float> _defaultPlayer2Pos;
};