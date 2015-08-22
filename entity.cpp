#include "entity.h"

#include "game.h"
#include "resources.h"

// --- Constructor ---

Entity::Entity(Game *game, const std::string &dataName)
  : sf::Sprite(), m_id(Game::newEntityId()), m_game(game)
{
  if (m_texture.loadFromFile(Resources::pngDataPath(dataName)))
  {
    m_texture.setSmooth(false);
    setTexture(m_texture);
  }
}

Entity::~Entity()
{
}

// --- Public ---

const int Entity::id()
{
  return m_id;
}
