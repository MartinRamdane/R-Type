/*
** EPITECH PROJECT, 2023
** InstanceButton.cpp
** File description:
** InstanceButton
*/
#ifndef B_CPP_500_MAR_5_1_RTYPE_MARTIN_RAMDANE_INSTANCEBUTTON_H
#define B_CPP_500_MAR_5_1_RTYPE_MARTIN_RAMDANE_INSTANCEBUTTON_H
#include <map>
#include <memory>
#include "../types/Instance.hpp"
#include "Entity.hpp"

class InstanceButton {
   public:
    InstanceButton(Instance instance, int instanceId, int x, int y);
    ~InstanceButton();
    std::string formatText(std::string toFormat);
    std::map<std::string, std::shared_ptr<Entity>> getEntities() { return _entities; }
    std::map<std::string, std::shared_ptr<sf::Text>> getTexts() { return _texts; }

   private:
    sf::Font _font;
    Instance _instance;
    int _instanceId;
    int _x;
    int _y;
    std::map<std::string, std::shared_ptr<Entity>> _entities;
    std::map<std::string, std::shared_ptr<sf::Text>> _texts;
};

#endif  //B_CPP_500_MAR_5_1_RTYPE_MARTIN_RAMDANE_INSTANCEBUTTON_H
