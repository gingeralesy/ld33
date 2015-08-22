#ifndef LEVERLODA_H
#define LEVERLODA_H

#include <list>
#include <SFML/Graphics.hpp>

#include "level.h"
#include "world.h"

class Game;

class Leverloda
{
public:
  static std::list<Level *> * loadLevels(Game *game);
  static int * loadWorld(const std::string &dataName,
                         unsigned int mapWidth,
                         unsigned int mapHeight);

private:
  static Level * firstLevel(Game *game);
};

#endif // LEVERLODA_H
