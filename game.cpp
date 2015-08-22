#include "game.h"

// --- Constructor ---

Game::Game(const std::string &title)
  : m_window(new sf::RenderWindow()), m_paused(false), m_delta(0)
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
  while (!m_entityList.empty())
  {
    Entity *e = m_entityList.front();
    m_entityList.pop_front();
    delete e;
  }
  m_entityMap.clear();

  sf::RenderWindow *tmpWin = m_window;
  m_window = 0;
  delete tmpWin;
}

// --- Public ---

void Game::addEntity(Entity *entity)
{
  m_entityList.push_back(entity);
}

float Game::delta()
{
  return m_delta;
}

Entity * Game::entity(const int &id)
{
  m_entityMap.at(id);
}

int Game::exec()
{
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
    for (std::list<Entity*>::iterator it = m_entityList.begin();
         it != m_entityList.end(); it++)
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
  for (std::list<Entity*>::iterator it = m_entityList.begin();
       it != m_entityList.end(); it++)
    m_window->draw(**it);

  m_window->display();
}

void Game::update()
{
  // Update objects here
  for (std::list<Entity*>::iterator it = m_entityList.begin();
       it != m_entityList.end(); it++)
  {
    Entity *e = *it;
    e->update(m_delta);
  }
}
