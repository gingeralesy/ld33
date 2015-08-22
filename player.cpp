#include "player.h"

Player::Player(Game *game, const std::string dataName)
  : Entity(game, dataName)
{
  sf::IntRect rect;
  rect.width = 32;
  rect.height = 32;
  setTextureRect(rect);
}

Player::~Player()
{

}

void Player::doEvent(const sf::Event &event)
{

}

void Player::update(const float &delta)
{

}
