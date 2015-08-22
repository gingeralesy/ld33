#include "level.h"

#include "resources.h"

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
