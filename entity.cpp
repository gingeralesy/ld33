#include "entity.h"

#include "game.h"

// --- Constructor ---

Entity::Entity(const sf::Image &image)
  : sf::Sprite(), m_id(Game::newEntityId())
{
  sf::Texture texture;
  texture.loadFromImage(image);
  setTexture(texture);
}

// --- Public ---

const int Entity::id()
{
  return m_id;
}
