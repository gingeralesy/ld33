#include "leverloda.h"

#include "game.h"
#include "player.h"

std::list<Level *> * Leverloda::loadLevels(Game *game)
{
  std::list<Level *> *levels = new std::list<Level *>();

  levels->push_back(firstLevel(game));

  return levels;
}

int * Leverloda::loadWorld(const std::string &dataName,
                           unsigned int mapWidth,
                           unsigned int mapHeight)
{
  int *map = new int[mapWidth * mapHeight];
  if (dataName == "level1")
  {
    srand((unsigned)time(0));
    for (unsigned int x = 0; x < mapWidth; x++)
    {
      for (unsigned int y = 0; y < mapHeight; y++)
      {
        unsigned int tileInMap = x + (y * mapWidth);
        map[tileInMap] = rand() % 3;
      }
    }
  }
  return map;
}

// -- Private --

Level * Leverloda::firstLevel(Game *game)
{
  Level *level = new Level(game,"level1");

  Player *player = new Player(game);
  player->setCenter(400.f,300.f);
  level->addEntity(player,Level::Player);

  return level;
}
