#include "building.h"

Building::Building(Game *game, const std::string &dataName)
  : Entity(game, dataName)
{

}

Building::Building(Game *game, const sf::Texture &texture)
  : Entity(game, texture)
{

}

void Building::doEvent(const sf::Event &event)
{

}

void Building::update(const float &delta)
{

}
