#ifndef GAME_H
#define GAME_H

#include <list>
#include <SFML/Graphics.hpp>

#include "entity.h"

class Game
{
public:
  explicit Game(const std::string &title);
  ~Game();

  void addEntity(Entity *entity);
  float delta();
  Entity * entity(const int &id);
  int exec();
  bool init();

  static int newEntityId();

private:
  void doEvent(const sf::Event &e);
  void draw();
  void update();

  sf::RenderWindow *m_window;
  bool m_paused;
  float m_delta;
  std::list<Entity *> m_entityList;
  std::map<const int, Entity *> m_entityMap;
};

#endif // GAME_H
