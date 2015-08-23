#include "player.h"

Player::Player(Game *game, const std::string dataName)
  : Entity(game, dataName)
{
  sf::IntRect rect;
  rect.width = 16;
  rect.height = 32;
  setTextureRect(rect);

  m_speed = 32.f * 4.5f;

  std::vector<float> frameTimes;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idle = new Animation(rect,0,0,frameTimes);
  m_animations[0] = idle;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walk = new Animation(rect,0,2,frameTimes);
  m_animations[1] = walk;
}

Player::~Player()
{
  if (!m_animations.empty())
  {
    std::map<sf::Uint32, Animation *>::iterator it;
    for (it = m_animations.begin(); it != m_animations.end(); it++)
      delete (*it).second;

    m_animations.clear();
  }
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

  Animation *animation = m_animations.at(0);
  if (m_vector.y > 0.f)
  {
    animation = m_animations.at(1);
  }

  setTextureRect(animation->getFrame(delta));
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
