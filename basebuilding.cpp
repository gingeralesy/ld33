#include "basebuilding.h"

BaseBuilding::BaseBuilding(Game *game, const sf::Texture &texture,
                           const sf::Vector2f &position)
  : Building(game, texture, position, sf::IntRect(0,0,32,32))
{

}

void BaseBuilding::doEvent(const sf::Event &event)
{

}

void BaseBuilding::update(const float &delta)
{

}
