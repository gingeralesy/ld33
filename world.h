#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <SFML/Graphics.hpp>

class Game;

class World : public sf::Drawable, public sf::Transformable
{
public:
  explicit World(Game *game,
                 const std::string &dataName,
                 unsigned int mapWidth = 128,
                 unsigned int mapHeight = 64,
                 sf::Vector2u tileSize = sf::Vector2u(16,16));
  ~World();

  const sf::Uint32 mapWidth() const;
  const sf::Uint32 mapHeight() const;
  const sf::Vector2u tileSize() const;

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  Game *m_game;
  unsigned int *m_map;
  const sf::Uint32 m_mapWidth;
  const sf::Uint32 m_mapHeight;
  const sf::Vector2u m_tileSize;
  sf::VertexArray m_vertices;
  sf::VertexArray m_verticesSandEdges;
  sf::VertexArray m_verticesGrassEdges;
  sf::Vertex *m_toDraw;
  sf::Texture m_tileset;
};

#endif // WORLD_H
