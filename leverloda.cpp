#include "leverloda.h"

#include "game.h"
#include "player.h"

std::list<Level *> * Leverloda::loadLevels(Game *game)
{
  std::list<Level *> *levels = new std::list<Level *>();

  levels->push_back(firstLevel(game));

  return levels;
}

sf::Uint32 * Leverloda::loadWorld(const std::string &dataName,
                                  sf::Uint32 mapWidth,
                                  sf::Uint32 mapHeight)
{
  static const sf::Uint32 tileTypes = 3;

  sf::Uint32 *map = new sf::Uint32[mapWidth * mapHeight];
  if (dataName == "level1")
  {
    sf::Uint32 *points = new sf::Uint32[tileTypes];

    srand((unsigned)time(0));
    for (sf::Uint32 x = 0; x < mapWidth; x++)
    {
      for (sf::Uint32 y = 0; y < mapHeight; y++)
      {
        sf::Uint32
            leftTile = rand() % tileTypes,
            upperLeftTile = rand() % tileTypes,
            upperTile = rand() % tileTypes,
            upperRightTile = rand() % tileTypes,
            tileInMap = x + (y * mapWidth);
        if (x > 0)
        {
          leftTile = map[tileInMap - 1];
          if (y > 0)
            upperLeftTile = map[tileInMap - 1 - mapWidth];
        }

        if (y > 0)
        {
          upperTile = map[tileInMap - mapWidth];

          if (x < mapWidth - 1)
            upperRightTile = map[tileInMap + 1 - mapWidth];
        }

        sf::Uint32 totalPoints = 0;
        for (sf::Uint32 i = 0; i < tileTypes; i++)
        {
          points[i] = 1;
          if (leftTile == i)
            points[i] += 1;
          if (upperLeftTile == i)
            points[i] += 1;
          if (upperTile == i)
            points[i] += 1;
          if (upperRightTile == i)
            points[i] += 1;

          totalPoints += points[i];
        }

        sf::Uint32 rVal = static_cast<sf::Uint32>(rand()) % totalPoints;
        totalPoints = 0;
        for (sf::Uint32 i = 0; i < tileTypes; i++)
        {
          if (totalPoints + points[i] > rVal)
          {
            map[tileInMap] = i;
            break;
          }
          totalPoints += points[i];
        }
      }
    }

    delete points;
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
