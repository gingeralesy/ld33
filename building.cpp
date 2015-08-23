#include "building.h"

Building::Building(Game *game, const std::string &dataName,
                   const sf::Vector2f &position,
                   const sf::IntRect &tile)
  : Entity(game, dataName, tile)
{
  setPosition(position);
}

Building::Building(Game *game, const sf::Texture &texture,
                   const sf::Vector2f &position,
                   const sf::IntRect &tile)
  : Entity(game, texture, tile)
{
  setPosition(position);
}
