#include "leverloda.h"

#include "game.h"
#include "player.h"

std::list<Level *> * Leverloda::loadLevels(Game *game)
{
  std::list<Level *> *levels = new std::list<Level *>();

  levels->push_back(firstLevel(game));

  return levels;
}

Level * Leverloda::firstLevel(Game *game)
{
  Level *level = new Level(game,"level1");

  level->addEntity(new Player(game));

  return level;
}
