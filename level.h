#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include <map>
#include <SFML/Graphics.hpp>

#include "entity.h"
#include "world.h"
#include "building.h"

class Level
{
public:
  enum Layer
  {
    All = 0,
    WorldContent,
    WorldCreatures,
    PlayerLayer,
    Overlay
  };

  enum BuildingType
  {
    Base = 0,
    Tower = 1
  };

  explicit Level(Game *game, const std::string &dataName);
  ~Level();

  void addBuilding(const BuildingType &type, const sf::Vector2f &location);
  void addEntity(Entity *entity, const Layer &layer);
  std::list<Entity *> * entities(const Layer &layer = All);
  Entity * entity(const int &id);

  // --- Loop functions ---
  void doEvent(const sf::Event &e);
  void draw(sf::RenderTarget *rTarget);
  void update(const float &delta);

  const World * world() const;

private:
  Game *m_game;
  World *m_world;
  sf::Vector2f m_worldSize;
  sf::View m_standard;
  sf::View m_minimap;
  sf::RectangleShape m_minimapBG;
  sf::Texture m_buildingsTexture;

  std::multimap<const Layer, Entity *> m_entityLayers;
  std::map<const Entity::ID, Entity *> m_entityMap;
  std::map<const BuildingType, Building *> m_buildings;
};

#endif // LEVEL_H
