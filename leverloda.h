#ifndef LEVERLODA_H
#define LEVERLODA_H

#include <list>

#include "level.h"
#include "world.h"

class Game;

class Leverloda
{
public:
  static std::list<Level *> * loadLevels(Game *game);
  static World * loadWorld(const std::string &dataName);

private:
  static Level * firstLevel(Game *game);
};

#endif // LEVERLODA_H
