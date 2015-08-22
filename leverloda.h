#ifndef LEVERLODA_H
#define LEVERLODA_H

#include <list>

#include "level.h"

class Game;

class Leverloda
{
public:
  static std::list<Level *> * loadLevels(Game *game);

private:
  static Level * firstLevel(Game *game);
};

#endif // LEVERLODA_H
