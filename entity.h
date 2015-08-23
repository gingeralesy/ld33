#ifndef ENTITY_H
#define ENTITY_H

#include <map>
#include <SFML/Graphics.hpp>

#include "animation.h"

class Game;

class Entity : public sf::Sprite
{
public:
  typedef int ID;

  explicit Entity(Game *game, const std::string &dataName);
  ~Entity();

  virtual void doEvent(const sf::Event &event) = 0;
  virtual void update(const float &delta) = 0;

  const ID id();
  const sf::Vector2f center();
  const void setCenter(sf::Vector2f pos);
  const void setCenter(float x, float y);

protected:
  const ID m_id;
  Game *m_game;
  sf::Texture m_texture;
  sf::Vector2f m_vector;
  float m_speed;
  std::map<sf::Uint32, Animation *> m_animations;
};

#endif // ENTITY_H
