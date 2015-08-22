#include "entity.h"

#include "game.h"
#include "resources.h"

// --- Constructor ---

Entity::Entity(const std::string &dataName)
  : sf::Sprite(), m_id(Game::newEntityId())
{
  sf::Texture texture;
  texture.loadFromFile(Resources::pngDataPath(dataName));
  setTexture(texture);
}

// --- Public ---

const int Entity::id()
{
  return m_id;
}
