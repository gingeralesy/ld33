#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <SFML/Graphics.hpp>

class World : public sf::Drawable, public sf::Transformable
{
public:
  explicit World(const std::string &dataName,
                 unsigned int mapWidth = 128,
                 unsigned int mapHeight = 64,
                 sf::Vector2u tileSize = sf::Vector2u(32,32));
  ~World();

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  unsigned int *m_map;
  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};

#endif // WORLD_H
