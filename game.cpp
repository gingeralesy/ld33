#include "game.h"

#include <SFML/Graphics.hpp>

#include "leverloda.h"
#include "resources.h"

// --- Constructor ---

Game::Game(const std::string &title)
  : m_window(new sf::RenderWindow()), m_currentLevel(-1),
    m_started(false), m_paused(false), m_delta(0.f)
{
  m_window->create(sf::VideoMode(800, 600, 32), title,
                   sf::Style::Titlebar | sf::Style::Close);
  m_window->setVerticalSyncEnabled(true);
  m_window->setFramerateLimit(60);
  m_window->setMouseCursorVisible(false);

  m_fixed = m_window->getView();
}

// --- Deconstructor ---

Game::~Game()
{
  while (!m_levels.empty())
  {
    Level *level = m_levels.back();
    m_levels.pop_back();
    delete level;
  }

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

  sf::RectangleShape pauseOverlay;
  pauseOverlay.setPosition(0,0);
  pauseOverlay.setSize(sf::Vector2f(m_window->getSize().x,
                                    m_window->getSize().y));
  pauseOverlay.setFillColor(sf::Color(0,0,0,128));

  sf::Font font;
  font.loadFromFile(Resources::ttfDataPath("blamdude"));
  sf::Text pauseText;
  pauseText.setFont(font);
  pauseText.setString("Paused");
  pauseText.setColor(sf::Color::White);

  sf::FloatRect rect = pauseText.getGlobalBounds();
  pauseText.setPosition(sf::Vector2f(m_window->getSize().x / 2.f -
                                       rect.width / 2.f,
                                     m_window->getSize().y / 2.f -
                                       rect.height / 2.f));

  Level *cLevel = level();
  sf::Clock clock;
  while (m_window->isOpen())
  {
    sf::Event e;
    while (m_window->pollEvent(e))
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
        cLevel->doEvent(e);
        break;
      }
    }

    if (m_paused)
    {
      clock.restart();
    }
    else
    {
      m_delta = clock.restart().asSeconds();
      cLevel->update(m_delta);
    }

    cLevel->draw(m_window);

    if (m_paused)
    {
      m_window->draw(pauseOverlay);
      m_window->draw(pauseText);
    }

    m_window->display();
  }

  return EXIT_SUCCESS;
}

const sf::View Game::fixedView()
{
  return m_fixed;
}

bool Game::init()
{
  if (m_started)
    return false;

  std::list<Level *> * levels = Leverloda::loadLevels(this);
  for (std::list<Level *>::iterator it = levels->begin();
       it != levels->end(); it++)
    m_levels.push_back((Level *)(*it));
  levels->clear();
  delete levels;

  m_currentLevel = 0;

  return true;
}

const sf::RenderWindow * Game::window()
{
  return m_window;
}

// -- Static --

int Game::newEntityId()
{
  static int idCounter = 0;
  int newId = idCounter;
  idCounter++;
  return newId;
}
