#ifndef BUILDING_H
#define BUILDING_H

#include "entity.h"

class Building : public Entity
{
public:
  explicit Building(Game *game, const std::string &dataName,
                    const sf::Vector2f &position,
                    const sf::IntRect &tile);
  explicit Building(Game *game, const sf::Texture &texture,
                    const sf::Vector2f &position,
                    const sf::IntRect &tile);

  virtual void doEvent(const sf::Event &event) = 0;
  virtual void update(const float &delta) = 0;
};

#endif // BUILDING_H
