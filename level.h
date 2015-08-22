#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include <map>
#include <SFML/Graphics.hpp>

#include "entity.h"

class Level
{
public:
  enum Layer
  {
    All,
    WorldTiles,
    WorldContent,
    WorldCreatures,
    Player,
    Interface
  };

  explicit Level(Game *game, std::string dataName);
  ~Level();

  void addEntity(Entity *entity, const Layer &layer);
  std::list<Entity *> * entities(const Layer &layer = All);
  Entity * entity(const int &id);

  // --- Loop functions ---
  void doEvent(const sf::Event &e);
  void draw(sf::RenderTarget *rTarget);
  void update(const float &delta);

private:
  Game *m_game;
  sf::Texture m_tileset;
  std::multimap<const Layer, Entity *> m_entityLayers;
  std::map<const Entity::ID, Entity *> m_entityMap;
};

#endif // LEVEL_H
