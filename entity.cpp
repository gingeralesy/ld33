#include "entity.h"

#include "game.h"
#include "resources.h"

// --- Constructor ---

Entity::Entity(Game *game, const std::string &dataName)
  : sf::Sprite(), m_id(Game::newEntityId()), m_game(game)
{
  sf::Texture texture;
  if (texture.loadFromFile(Resources::pngDataPath(dataName)))
  {
    texture.setSmooth(false);
    setTexture(texture);
  }
}

// --- Public ---

const int Entity::id()
{
  return m_id;
}
