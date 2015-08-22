#include "game.h"

// --- Constructor ---

Game::Game(const std::string &title)
  : m_window(new sf::RenderWindow()), m_currentLevel(0),
    m_started(false), m_paused(false), m_delta(0)
{
  m_window->create(sf::VideoMode(800, 600, 32), title,
                   sf::Style::Titlebar | sf::Style::Close);
  m_window->setVerticalSyncEnabled(true);
  m_window->setFramerateLimit(60);
  m_window->setMouseCursorVisible(false);
}

// --- Deconstructor ---

Game::~Game()
{
  if (m_window)
  {
    sf::RenderWindow *tmpWin = m_window;
    m_window = 0;
    delete tmpWin;
  }
}

// --- Public ---

Level * Game::level(int levelNum)
{
  if (levelNum == -1 || levelNum )
    return m_levels.at(m_currentLevel);
  return m_levels.at(levelNum);
}

float Game::delta()
{
  return m_delta;
}

int Game::exec()
{
  if (m_started)
    return EXIT_SUCCESS;
  m_started = true;

  sf::Clock clock;
  while (m_window->isOpen())
  {
    sf::Event e;
    while (m_window->pollEvent(e))
      doEvent(e);

    if (m_paused)
    {
      clock.restart();
    }
    else
    {
      m_delta = clock.restart().asSeconds();
      update();
    }
    draw();
  }

  return EXIT_SUCCESS;
}

bool Game::init()
{
  if (m_started)
    return false;

  return true;
}

// -- Static --

int Game::newEntityId()
{
  static int idCounter = 0;
  int newId = idCounter;
  idCounter++;
  return newId;
}

// --- Private ---

void Game::doEvent(const sf::Event &e)
{
  switch (e.type)
  {
  case sf::Event::Closed:
    m_window->close();
    break;
  case sf::Event::LostFocus:
    m_paused = true;
    break;
  case sf::Event::GainedFocus:
    m_paused = false;
    break;
  default:
    for (std::list<Entity*>::iterator it = level()->entities().begin();
         it != level()->entities().end(); it++)
    {
      Entity *entity = *it;
      entity->doEvent(e);
    }
    break;
  }
}

void Game::draw()
{
  m_window->clear(sf::Color::Black);

  // Draw objects here
  for (std::list<Entity*>::iterator it = level()->entities().begin();
       it != level()->entities().end(); it++)
    m_window->draw(**it);

  m_window->display();
}

void Game::update()
{
  // Update objects here
  for (std::list<Entity*>::iterator it = level()->entities().begin();
       it != level()->entities().end(); it++)
  {
    Entity *e = *it;
    e->update(m_delta);
  }
}
