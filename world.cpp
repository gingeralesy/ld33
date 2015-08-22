#include "world.h"
#include "leverloda.h"

#include "resources.h"

World::World(const std::string &dataName,
             sf::Uint32 mapWidth,
             sf::Uint32 mapHeight,
             sf::Vector2u tileSize)
  : m_map(Leverloda::loadWorld(dataName, mapWidth, mapHeight))
{
  if (m_tileset.loadFromFile(Resources::pngDataPath(dataName)))
  {
    m_tileset.setSmooth(false);

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(128 * 64 * 4);

    sf::Uint32 tilesPerX = m_tileset.getSize().x / tileSize.x;
    for (sf::Uint32 x = 0; x < mapWidth; x++)
    {
      for (sf::Uint32 y = 0; y < mapHeight; y++)
      {
        sf::Uint32 tileInMap = x + y * mapWidth;
        sf::Uint32 tileValue = m_map[tileInMap];
        sf::Uint32 tu = tileValue % tilesPerX;
        sf::Uint32 tv = tileValue / tilesPerX;

        sf::Vertex *quad = &m_vertices[tileInMap * 4];

        quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
        quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
        quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
      }
    }
  }
}

World::~World()
{
  if (m_map)
  {
    sf::Uint32 *tmpMap = m_map;
    m_map = 0;
    delete tmpMap;
  }
}

void World::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  states.texture = &m_tileset;
  target.draw(m_vertices, states);
}
