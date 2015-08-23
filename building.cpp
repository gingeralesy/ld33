#include "building.h"

Building::Building(Game *game, const std::string &dataName,
                   const sf::Vector2f &position,
                   const sf::IntRect &tileSize)
  : Entity(game, dataName, tileSize)
{
  setPosition(position);
}

Building::Building(Game *game, const sf::Texture &texture,
                   const sf::Vector2f &position,
                   const sf::IntRect &tileSize)
  : Entity(game, texture, tileSize)
{
  setPosition(position);
}
