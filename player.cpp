#include "player.h"

#include "game.h"
#include "level.h"
#include "world.h"
#include "util.h"

Player::Player(Game *game, const std::string dataName)
  : Entity(game, dataName, sf::IntRect(0,0,16,32), sf::IntRect(0,16,16,16))
{
  setTextureRect(m_tile);

  m_speed = 32.f * 4.5f;

  std::vector<float> frameTimes;
  Facing dir = South;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleSouth = new Animation(m_tile,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleSouth;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkSouth = new Animation(m_tile,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkSouth;

  frameTimes.clear();
  dir = East;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleEast = new Animation(m_tile,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleEast;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkEast = new Animation(m_tile,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkEast;

  frameTimes.clear();
  dir = North;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleNorth = new Animation(m_tile,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleNorth;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkNorth = new Animation(m_tile,dir,2,frameTimes);
  m_animations[dir * 10 + 1] = walkNorth;

  frameTimes.clear();
  dir = West;
  frameTimes.push_back(1.f);
  frameTimes.push_back(1.f);
  Animation *idleWest = new Animation(m_tile,dir,0,frameTimes);
  m_animations[dir * 10 + 0] = idleWest;

  frameTimes.clear();
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  frameTimes.push_back(0.15f);
  Animation *walkWest = new Animation(m_tile,dir,2,frameTimes);
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
  const sf::Vector2f pos = getPosition();

  float
      xSpeed = m_vector.x * m_speed * delta,
      ySpeed = m_vector.y * m_speed * delta;

  if (m_vector.x != 0.f)
    ySpeed /= 2.f;
  if (m_vector.y != 0.f)
    xSpeed /= 2.f;

  float x = pos.x + xSpeed;
  float y = pos.y + ySpeed;
  const sf::Vector2f stopPoint(x, y);
  setPosition(stopPoint);

  std::list<Entity *> entities;
  m_game->level()->entities(&entities);

  std::list<Entity *>::iterator it;
  for (it = entities.begin(); it != entities.end(); it++)
  {
    Entity *en = (*it);
    if (en->id() != id())
    {
      sf::IntRect mHitbox = hitbox();
      sf::IntRect eHitbox = en->hitbox();
      if (mHitbox.intersects(eHitbox))
      {
        // TODO: make it "slide"
        /*
    Vector normal = objects[i].CheckCollision(newPos.x, newPos.y, newPos.z, direction.x, direction.y, direction.z);
    if(normal != Vector::NullVector())
    {
        Vector invNormal = normal.Negative();
        invNormal = invNormal * (direction * normal).Length(); // Change normal to direction's length and normal's axis
        Vector wallDir = direction - invNormal;
        newPos = oldPos + wallDir;
        direction = newPos - oldPos;
    }
         */
        sf::Vector2f eTopLeft(eHitbox.left, eHitbox.top);
        sf::Vector2f eBotRight(eHitbox.left + eHitbox.width,
                               eHitbox.top + eHitbox.height);

        sf::Vector2f intersection;
        if (Util::linesCollide(eTopLeft, sf::Vector2f(eTopLeft.x, eBotRight.y),
                               pos, stopPoint, &intersection))
        {
          // From left
          x = eHitbox.left - mHitbox.width;
          setPosition(x, y);
        }
        else
        {
          setPosition(pos.x, pos.y);
        }
        break;
      }
    }
  }

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
    if (m_facing == West)
    {
      if (m_vector.y > 0.f)
        m_facing = South;
      else if (m_vector.y < 0.f)
        m_facing = North;
    }
    break;
  case sf::Keyboard::Right:
    if (m_vector.x > 0.f)
      m_vector.x = 0.f;
    if (m_facing == East)
    {
      if (m_vector.y > 0.f)
        m_facing = South;
      else if (m_vector.y < 0.f)
        m_facing = North;
    }
    break;
  case sf::Keyboard::Up:
    if (m_vector.y < 0.f)
      m_vector.y = 0.f;
    if (m_facing == North)
    {
      if (m_vector.x > 0.f)
        m_facing = East;
      else if (m_vector.x < 0.f)
        m_facing = West;
    }
    break;
  case sf::Keyboard::Down:
    if (m_vector.y > 0.f)
      m_vector.y = 0.f;
    if (m_facing == South)
    {
      if (m_vector.x > 0.f)
        m_facing = East;
      else if (m_vector.x < 0.f)
        m_facing = West;
    }
    break;
  }
}
