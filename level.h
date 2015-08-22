#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include <map>
#include <SFML/Graphics.hpp>

#include "entity.h"
#include "world.h"

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

  explicit Level(Game *game, const std::string &dataName);
  ~Level();

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

  std::multimap<const Layer, Entity *> m_entityLayers;
  std::map<const Entity::ID, Entity *> m_entityMap;
};

#endif // LEVEL_H
