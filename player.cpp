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
  switch (event.type)
  {
  case sf::Event::KeyPressed:
    keyPressed(event.key.code);
    break;
  case sf::Event::KeyReleased:
    keyReleased(event.key.code);
    break;
  }
}

void Player::update(const float &delta)
{
  sf::Vector2f pos = getPosition();
  float x = pos.x + m_vector.x * m_speed * delta;
  float y = pos.y + m_vector.y * m_speed * delta;
  setPosition(x,y);
}


// PPrivate

void Player::keyPressed(const sf::Keyboard::Key &key)
{
  switch (key)
  {
  case sf::Keyboard::Left:
    m_vector.x = -1.f;
    break;
  case sf::Keyboard::Right:
    m_vector.x = 1.f;
    break;
  case sf::Keyboard::Up:
    m_vector.y = -1.f;
    break;
  case sf::Keyboard::Down:
    m_vector.y = 1.f;
    break;
  }
}

void Player::keyReleased(const sf::Keyboard::Key &key)
{
  switch (key)
  {
  case sf::Keyboard::Left:
    if (m_vector.x < 0.f)
      m_vector.x = 0.f;
    break;
  case sf::Keyboard::Right:
    if (m_vector.x > 0.f)
      m_vector.x = 0.f;
    break;
  case sf::Keyboard::Up:
    if (m_vector.y < 0.f)
      m_vector.y = 0.f;
    break;
  case sf::Keyboard::Down:
    if (m_vector.y > 0.f)
      m_vector.y = 0.f;
    break;
  }
}
