#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Game;

class Entity : public sf::Sprite
{
public:
  explicit Entity(Game *game, const std::string &dataName);
  virtual ~Entity() {}

  virtual void doEvent(const sf::Event &event) = 0;
  virtual void update(const float &delta) = 0;

  const int id();

private:
  const int m_id;
  Game *m_game;
};

#endif // ENTITY_H
