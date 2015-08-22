#ifndef GAME_H
#define GAME_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "level.h"

class Game
{
public:
  explicit Game(const std::string &title);
  ~Game();

  Level * level(int levelNum = -1);
  float delta();
  int exec();
  bool init();

  static int newEntityId();

private:
  void doEvent(const sf::Event &e);
  void draw();
  void update();

  sf::RenderWindow *m_window;
  std::vector<Level *> m_levels;
  int m_currentLevel;
  bool m_started;
  bool m_paused;
  float m_delta;
};

#endif // GAME_H
