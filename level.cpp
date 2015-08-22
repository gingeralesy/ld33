#include "level.h"

#include "resources.h"
#include "game.h"

Level::Level(Game *game, std::string dataName)
  : m_game(game)
{
  if (m_tileset.loadFromFile(Resources::pngDataPath(dataName)))
  {
    m_tileset.setSmooth(false);
  }
}

Level::~Level()
{
  m_entityMap.clear();
  while (!m_entityList.empty())
  {
    Entity *e = m_entityList.front();
    m_entityList.pop_front();
    delete e;
  }
}

void Level::addEntity(Entity *entity)
{
  m_entityList.push_back(entity);
  m_entityMap[entity->id()] = entity;
}

std::list<Entity *> Level::entities()
{
  return m_entityList;
}

Entity * Level::entity(const int &id)
{
  m_entityMap.at(id);
}

// --- Loop functions ---
void Level::doEvent(const sf::Event &e)
{
  if (!m_entityList.empty())
  {
    for (std::list<Entity*>::iterator it = m_entityList.begin();
         it != m_entityList.end(); it++)
    {
      Entity *entity = *it;
      entity->doEvent(e);
    }
  }
}

void Level::draw(sf::RenderTarget *rTarget)
{
  // Draw objects here
  rTarget->clear(sf::Color::Black);
  if (!m_entityList.empty())
  {
    for (std::list<Entity*>::iterator it = m_entityList.begin();
         it != m_entityList.end(); it++)
      rTarget->draw(**it);
  }
}

void Level::update()
{
  // Update objects here
  if (!m_entityList.empty())
  {
    for (std::list<Entity*>::iterator it = m_entityList.begin();
         it != m_entityList.end(); it++)
    {
      Entity *e = *it;
      e->update(m_game->delta());
    }
  }
}
