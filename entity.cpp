#include "entity.h"

#include "game.h"
#include "resources.h"

// --- Constructor ---

Entity::Entity(Game *game, const std::string &dataName)
  : sf::Sprite(), m_id(Game::newEntityId()), m_game(game),
    m_texture(new sf::Texture)
{
  if (m_texture->loadFromFile(Resources::pngDataPath(dataName)))
  {
    m_texture->setSmooth(false);
    setTexture(*m_texture);
  }
}

Entity::~Entity()
{
  if (m_texture)
  {
    sf::Texture *tmpText = m_texture;
    m_texture = 0;
    tmpText = 0;
  }
}

// --- Public ---

const int Entity::id()
{
  return m_id;
}
