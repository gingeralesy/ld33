#include "towerbuilding.h"

TowerBuilding::TowerBuilding(Game *game, const sf::Texture &texture,
                             const sf::Vector2f &position)
  : Building(game, texture, position, sf::IntRect(32,0,32,32))
{

}

void TowerBuilding::doEvent(const sf::Event &event)
{

}

void TowerBuilding::update(const float &delta)
{

}
