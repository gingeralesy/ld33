#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include <map>

#include "entity.h"

class Level
{
public:
  explicit Level(Game *game, std::string dataName = "level");
  ~Level();

  void addEntity(Entity *entity);
  std::list<Entity *> entities();
  Entity * entity(const int &id);

private:
  Game *m_game;
  sf::Texture m_tileset;
  std::list<Entity *> m_entityList;
  std::map<const int, Entity *> m_entityMap;
};

#endif // LEVEL_H
