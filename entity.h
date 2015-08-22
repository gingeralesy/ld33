#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Game;

class Entity : public sf::Sprite
{
public:
  explicit Entity(Game *game, const std::string &dataName);
  ~Entity();

  virtual void doEvent(const sf::Event &event) = 0;
  virtual void update(const float &delta) = 0;

  const int id();
  const sf::Vector2f center();
  const void setCenter(sf::Vector2f pos);
  const void setCenter(float x, float y);

protected:
  const int m_id;
  Game *m_game;
  sf::Texture m_texture;
  sf::Vector2f m_vector;
  float m_speed;
};

#endif // ENTITY_H
