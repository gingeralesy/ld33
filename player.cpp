#include "player.h"

Player::Player(Game *game, const std::string dataName)
  : Entity(game, dataName, sf::IntRect(0,0,16,32))
{
  setTextureRect(m_tileSize);

  m_speed = 32.f * 4.5f;

  std::vector<float> frameTimes;
  Facing dir = South;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleSouth = new Animation(m_tileSize,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleSouth;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkSouth = new Animation(m_tileSize,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkSouth;

  frameTimes.clear();
  dir = East;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleEast = new Animation(m_tileSize,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleEast;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkEast = new Animation(m_tileSize,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkEast;

  frameTimes.clear();
  dir = North;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleNorth = new Animation(m_tileSize,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleNorth;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkNorth = new Animation(m_tileSize,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkNorth;

  frameTimes.clear();
  dir = West;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleWest = new Animation(m_tileSize,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleWest;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkWest = new Animation(m_tileSize,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkWest;
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

  Animation *animation = m_animations.at(m_facing * 10 + 0);
  if (m_vector.x != 0.f || m_vector.y != 0.f)
    animation = m_animations.at(m_facing * 10 + 1);

  setTextureRect(animation->getFrame(delta));
}


// PPrivate

void Player::keyPressed(const sf::Keyboard::Key &key)
{
  switch (key)
  {
  case sf::Keyboard::Left:
    m_vector.x = -1.f;
    m_facing = West;
    break;
  case sf::Keyboard::Right:
    m_vector.x = 1.f;
    m_facing = East;
    break;
  case sf::Keyboard::Up:
    m_vector.y = -1.f;
    m_facing = North;
    break;
  case sf::Keyboard::Down:
    m_vector.y = 1.f;
    m_facing = South;
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
