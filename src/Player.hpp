/*
** EPITECH PROJECT, 2023
** Player.hpp
** File description:
** Player
*/

#ifndef HEADER_PLAYER
  #define HEADER_PLAYER
#include <string>
#include "IEntity.hpp"

class Player : public IEntity {
  public:
    Player();
    ~Player(){};
    int getXPos();
    int getYPos();
    void setXPos(int x);
    void setYPos(int y);
    void setPlayerName(std::string name);


  protected:
  private:
    int _x;
    int _y;
    std::string _playerName;
};

#endif /* !HEADER_PLAYER */
