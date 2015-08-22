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

  std::list<Entity *> *entityList = entities();
  m_entityLayers.clear();

  while (!entityList->empty())
  {
    Entity *e = entityList->front();
    entityList->pop_front();
    delete e;
  }
  delete entityList;
}

void Level::addEntity(Entity *entity, const Layer &layer)
{
  m_entityLayers.insert(std::make_pair(layer,entity));
  m_entityMap[entity->id()] = entity;
}

std::list<Entity *> * Level::entities(const Layer &layer)
{
  std::list<Entity *> *entities = new std::list<Entity *>();
  if (!m_entityLayers.empty())
  {
    std::multimap<Layer, Entity *>::iterator it;
    if (layer == All)
    {
      for (it = m_entityLayers.begin(); it != m_entityLayers.end(); it++)
        entities->push_back((*it).second);
    }
    else
    {
      for (it = m_entityLayers.lower_bound(layer);
           it != m_entityLayers.upper_bound(layer); it++)
        entities->push_back((*it).second);
    }
  }
  return entities;
}

Entity * Level::entity(const int &id)
{
  m_entityMap.at(id);
}

// --- Loop functions ---
void Level::doEvent(const sf::Event &e)
{
  if (!m_entityLayers.empty())
  {
    for (std::multimap<Layer, Entity *>::iterator it = m_entityLayers.begin();
         it != m_entityLayers.end(); it++)
    {
      Entity *entity = (*it).second;
      entity->doEvent(e);
    }
  }
}

void Level::draw(sf::RenderTarget *rTarget)
{
  // Draw objects here
  rTarget->clear(sf::Color::Black);
  if (!m_entityLayers.empty())
  {
    for (std::multimap<Layer, Entity *>::iterator it = m_entityLayers.begin();
         it != m_entityLayers.end(); it++)
    {
      Entity *e = (*it).second;
      rTarget->draw(*e);
    }
  }
}

void Level::update(const float &delta)
{
  // Update objects here
  if (!m_entityLayers.empty())
  {
    for (std::multimap<Layer, Entity *>::iterator it = m_entityLayers.begin();
         it != m_entityLayers.end(); it++)
    {
      Entity *e = (*it).second;
      e->update(delta);
    }
  }
}
