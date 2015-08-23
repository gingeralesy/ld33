#ifndef BUILDING_H
#define BUILDING_H

#include "entity.h"

class Building : public Entity
{
public:
  explicit Building(Game *game, const std::string &dataName);
  explicit Building(Game *game, const sf::Texture &texture);

  void doEvent(const sf::Event &event);
  void update(const float &delta);
};

#endif // BUILDING_H
