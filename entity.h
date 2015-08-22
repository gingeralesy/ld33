#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity : public sf::Sprite
{
public:
  explicit Entity(const std::string &dataName);
  virtual ~Entity() {}

  virtual void doEvent(const sf::Event &event) = 0;
  virtual void update(const float &delta) = 0;

  const int id();

private:
  const int m_id;
};

#endif // ENTITY_H
