#ifndef BASEBUILDING_H
#define BASEBUILDING_H

#include <SFML/Graphics.hpp>

#include "building.h"

class BaseBuilding : public Building
{
public:
  explicit BaseBuilding(Game *game, const sf::Texture &texture,
                        const sf::Vector2f &position);

  void doEvent(const sf::Event &event);
  virtual void update(const float &delta);
};

#endif // BASEBUILDING_H
