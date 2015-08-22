#include "leverloda.h"

#include "game.h"
#include "player.h"

std::list<Level *> * Leverloda::loadLevels(Game *game)
{
  std::list<Level *> *levels = new std::list<Level *>();

  levels->push_back(firstLevel(game));

  return levels;
}

World * Leverloda::loadWorld(const std::string &dataName)
{

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
