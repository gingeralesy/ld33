#include "leverloda.h"

#include "game.h"

std::list<Level *> * Leverloda::loadLevels(Game *game)
{
  std::list<Level *> *levels = new std::list<Level *>();

  levels->push_back(firstLevel(game));

  return levels;
}

Level * Leverloda::firstLevel(Game *game)
{
  Level *level = new Level(game);


  return level;
}
