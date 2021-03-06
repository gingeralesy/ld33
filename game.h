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
  const sf::View fixedView();
  bool init();
  const sf::RenderWindow * window();

  static int newEntityId();

private:
  sf::RenderWindow *m_window;
  sf::View m_fixed;
  std::vector<Level *> m_levels;
  int m_currentLevel;
  bool m_started;
  bool m_paused;
  float m_delta;
};

#endif // GAME_H
