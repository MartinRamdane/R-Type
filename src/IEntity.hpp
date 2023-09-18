/*
** EPITECH PROJECT, 2023
** Entity.hpp
** File description:
** Entity
*/

#ifndef HEADER_IENTITY
  #define HEADER_IENTITY
#include <iostream>

class IEntity {
  public:
    virtual ~IEntity() = default;
    virtual int getXPos() = 0;
    virtual int getYPos() = 0;
    virtual void setXPos(int) = 0;
    virtual void setYPos(int) = 0;

  protected:
  private:
};

#endif /* !HEADER_ENTITY */
