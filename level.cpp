#include "level.h"

#include <math.h>

#include "resources.h"
#include "game.h"
#include "basebuilding.h"
#include "towerbuilding.h"

Level::Level(Game *game, const std::string &dataName)
  : m_game(game), m_world(new World(dataName))
{
  m_buildingsTexture.loadFromFile(Resources::pngDataPath("buildings"));

  sf::View fixed = m_game->fixedView();
  m_standard = fixed;
  m_standard.zoom(0.5f);

  m_worldSize.x =
    static_cast<float>(m_world->mapWidth() * m_world->tileSize().x);
  m_worldSize.y =
    static_cast<float>(m_world->mapHeight() * m_world->tileSize().y);

  float zoom = m_worldSize.x / 200.f;
  m_minimap =
    sf::View(sf::FloatRect(m_worldSize.x / 2.f,
                           m_worldSize.y / 2.f,
                           m_worldSize.x / zoom,
                           m_worldSize.y / zoom));

  sf::Vector2f windowSize(static_cast<float>(m_game->window()->getSize().x),
                          static_cast<float>(m_game->window()->getSize().y));

  float
      mmVpWidth = m_minimap.getSize().x / windowSize.x,
      mmVpHeight = m_minimap.getSize().y / windowSize.y;

  m_minimap.setViewport(sf::FloatRect(1.f - mmVpWidth - 0.02f, 0.03f,
                                      mmVpWidth, mmVpHeight));
  m_minimap.zoom(zoom);
  m_minimap.setCenter(m_worldSize.x / 2.f, m_worldSize.y / 2.f);

  sf::FloatRect mmVp = m_minimap.getViewport();
  m_minimapBG.setPosition(mmVp.left * windowSize.x - 5.f,
                          mmVp.top * windowSize.y - 5.f);
  m_minimapBG.setSize(sf::Vector2f(mmVp.width * windowSize.x + 10.f,
                                   mmVp.height * windowSize.y + 10.f));
  m_minimapBG.setFillColor(sf::Color(8, 8, 160, 128));
}

Level::~Level()
{
  std::list<Entity *> *entityList = entities();
  m_entityMap.clear();
  m_entityLayers.clear();
  m_buildings.clear();
  while (!entityList->empty())
  {
    Entity *e = entityList->front();
    entityList->pop_front();
    delete e;
  }
  delete entityList;

  if (m_world)
  {
    World *tmpWorld = m_world;
    m_world = 0;
    delete tmpWorld;
  }
}

void Level::addBuilding(const BuildingType &type,
                        const sf::Vector2f &position)
{

  Building *building = 0;
  switch (type)
  {
  case Base:
    building =
      new BaseBuilding(m_game,m_buildingsTexture,position);
    break;
  case Tower:
    building =
      new TowerBuilding(m_game,m_buildingsTexture,position);
    break;
  }
  if (building)
  {
    m_buildings.push_back(building);
    addEntity(building, WorldContent);
  }
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
  if (e.type == sf::Event::KeyPressed)
  {
    switch (e.key.code)
    {
    case sf::Keyboard::PageUp:
      m_standard.zoom(-1.5f);
      break;
    case sf::Keyboard::PageDown:
      m_standard.zoom(1.5f);
      break;
    }
  }

  if (!m_entityLayers.empty())
  {
    std::multimap<Layer, Entity *>::iterator it;
    for (it = m_entityLayers.begin(); it != m_entityLayers.end(); it++)
    {
      Entity *entity = (*it).second;
      entity->doEvent(e);
    }
  }
}

void Level::draw(sf::RenderTarget *rTarget)
{
  // Draw objects here
  rTarget->clear(sf::Color(98, 146, 29));
  if (!m_entityLayers.empty())
  {
    std::multimap<Layer, Entity *>::iterator it;

    sf::Vector2f camCenter(m_standard.getSize().x / 2.f,
                           m_standard.getSize().y / 2.f);
    if (m_entityLayers.count(PlayerLayer) > 0)
    {
      Entity *player = (*m_entityLayers.find(PlayerLayer)).second;
      sf::Vector2f playerCenter = player->center();
      if (playerCenter.x > camCenter.x)
        camCenter.x = playerCenter.x;
      if (playerCenter.y > camCenter.y)
        camCenter.y = playerCenter.y;

      float maxX = m_worldSize.x - m_standard.getSize().x / 2.f;
      float maxY = m_worldSize.y - m_standard.getSize().y / 2.f;
      if (camCenter.x > maxX)
        camCenter.x = maxX;
      if (camCenter.y > maxY)
        camCenter.y = maxY;
    }

    // Draw the world background tiles
    rTarget->setView(m_standard);
    m_standard.setCenter(camCenter);

    rTarget->draw(*m_world);

    // Draw world contents
    for (it = m_entityLayers.lower_bound(WorldContent);
         it != m_entityLayers.upper_bound(PlayerLayer); it++)
    {
      Entity *e = (*it).second;
      rTarget->draw(*e);
    }

    // Draw the overlay
    if (m_entityLayers.count(Overlay) > 0)
    {
      rTarget->setView(m_game->fixedView());
      for (it = m_entityLayers.lower_bound(Overlay);
           it != m_entityLayers.upper_bound(Overlay); it++)
      {
        Entity *e = (*it).second;
        rTarget->draw(*e);
      }
    }

    // Draw minimap
    rTarget->setView(m_game->fixedView());
    rTarget->draw(m_minimapBG);

    rTarget->setView(m_minimap);
    for (it = m_entityLayers.lower_bound(WorldContent);
         it != m_entityLayers.upper_bound(PlayerLayer); it++)
    {
      Entity *e = (*it).second;
      sf::RectangleShape blip(sf::Vector2f(m_world->tileSize().x * 4.f,
                                           m_world->tileSize().y * 4.f));
      blip.setPosition(e->getPosition());
      blip.setFillColor(sf::Color(221, 42, 42, 221));
      rTarget->draw(blip);
    }
  }
  rTarget->setView(m_game->fixedView());
}

void Level::update(const float &delta)
{
  // Update objects here
  if (!m_entityLayers.empty())
  {
    std::multimap<Layer, Entity *>::iterator it;
    for (it = m_entityLayers.begin(); it != m_entityLayers.end(); it++)
    {
      Entity *e = (*it).second;
      e->update(delta);
    }
  }
}

const World * Level::world() const
{
  return m_world;
}
