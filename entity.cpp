#include "entity.h"

#include "game.h"
#include "resources.h"

// --- Constructor ---

Entity::Entity(Game *game, const std::string &dataName,
               const sf::IntRect &tileSize)
  : sf::Sprite(), m_id(Game::newEntityId()), m_game(game),
    m_tile(tileSize), m_facing(South)
{
  if (m_texture.loadFromFile(Resources::pngDataPath(dataName)))
  {
    m_texture.setSmooth(false);
    setTexture(m_texture);
  }
}

Entity::Entity(Game *game, const sf::Texture &texture,
               const sf::IntRect &tileSize)
  : sf::Sprite(), m_id(Game::newEntityId()), m_game(game),
    m_texture(texture), m_tile(tileSize), m_facing(South)
{
  m_texture.setSmooth(false);
  setTexture(m_texture);
}

Entity::~Entity()
{
}

// --- Public ---

const Entity::ID Entity::id()
{
  return m_id;
}

const sf::Vector2f Entity::center()
{
  sf::Vector2f pos = getPosition();
  sf::FloatRect rect = getGlobalBounds();
  return sf::Vector2f(pos.x + rect.width / 2.f,
                      pos.y + rect.height / 2.f);
}

const void Entity::setCenter(sf::Vector2f pos)
{
  setCenter(pos.x,pos.y);
}

const void Entity::setCenter(float x, float y)
{
  sf::FloatRect rect = getGlobalBounds();
  setPosition(sf::Vector2f(x - rect.width / 2.f,
                           y - rect.height / 2.f));
}
