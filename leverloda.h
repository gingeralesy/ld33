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
  static sf::Uint32 *loadWorld(const std::string &dataName,
                               sf::Uint32 mapWidth,
                               sf::Uint32 mapHeight);

private:
  static Level * firstLevel(Game *game);
};

#endif // LEVERLODA_H
