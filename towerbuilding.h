#ifndef TOWERBUILDING_H
#define TOWERBUILDING_H

#include <SFML/Graphics.hpp>

#include "building.h"

class TowerBuilding : public Building
{
public:
  explicit TowerBuilding(Game *game, const sf::Texture &texture,
                         const sf::Vector2f &position);

  void doEvent(const sf::Event &event);
  virtual void update(const float &delta);
};

#endif // TOWERBUILDING_H
