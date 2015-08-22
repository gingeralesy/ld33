#include "world.h"
#include "leverloda.h"

#include "resources.h"

World::World(const std::string &dataName,
             sf::Uint32 mapWidth,
             sf::Uint32 mapHeight,
             sf::Vector2u tileSize)
  : m_map(Leverloda::loadWorld(dataName, mapWidth, mapHeight)),
    m_mapWidth(mapWidth), m_mapHeight(mapHeight), m_tileSize(tileSize)
{
  if (m_tileset.loadFromFile(Resources::pngDataPath(dataName)))
  {
    m_tileset.setSmooth(false);

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(128 * 64 * 4);

    m_verticesSandEdges.setPrimitiveType(sf::Quads);
    m_verticesSandEdges.resize(128 * 64 * 4);

    m_verticesGrassEdges.setPrimitiveType(sf::Quads);
    m_verticesGrassEdges.resize(128 * 64 * 4);

    sf::Uint32 tilesPerX = m_tileset.getSize().x / tileSize.x;
    for (sf::Uint32 x = 0; x < mapWidth; x++)
    {
      for (sf::Uint32 y = 0; y < mapHeight; y++)
      {
        sf::Uint32 tileInMap = x + y * mapWidth;
        sf::Uint32 tileValue = m_map[tileInMap];
        sf::Uint32 tu = tileValue % tilesPerX;
        sf::Uint32 tv = tileValue / tilesPerX;

        // Bottom layer
        sf::Vertex *quad = &m_vertices[tileInMap * 4];

        quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
        quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
        quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        int
            tileLeftVal = -1,
            tileUpVal = -1,
            tileRightVal = -1,
            tileDownVal = -1;

        if (x > 0)
          tileLeftVal = m_map[tileInMap - 1];
        if (y > 0)
          tileUpVal = m_map[tileInMap - mapWidth];
        if (x < mapWidth - 1)
          tileRightVal = m_map[tileInMap + 1];
        if (y < mapHeight - 1)
          tileDownVal = m_map[tileInMap + mapWidth];

        // Sand layer
        quad = &m_verticesSandEdges[tileInMap * 4];

        quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
        quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
        quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

        tu = 3;
        tv = 0;
        if (tileValue == 2 &&
            (tileLeftVal == 1 || tileUpVal == 1 ||
             tileRightVal == 1 || tileDownVal == 1))
        {
          tv = 2;
          if (tileLeftVal == 1 && tileUpVal == 1 &&
              tileRightVal == 1 && tileDownVal == 1)
          {
            // Sand all around
            tu = 14;
          }
          else if (tileLeftVal == 1 && tileUpVal != 1 &
                   tileRightVal == 1 && tileDownVal == 1)
          {
            tu = 13;
          }
          else if (tileLeftVal != 1 && tileUpVal == 1 &&
                   tileRightVal == 1 && tileDownVal == 1)
          {
            tu = 12;
          }
          else if (tileLeftVal == 1 && tileUpVal == 1 &&
                   tileRightVal == 1 && tileDownVal != 1)
          {
            tu = 11;
          }
          else if (tileLeftVal == 1 && tileUpVal == 1 &&
                   tileRightVal != 1 && tileDownVal == 1)
          {
            tu = 10;
          }
          else if (tileLeftVal != 1 && tileUpVal != 1 &&
                   tileRightVal == 1 && tileDownVal == 1)
          {
            tu = 9;
          }
          else if (tileLeftVal != 1 && tileUpVal == 1 &&
                   tileRightVal != 1 && tileDownVal == 1)
          {
            tu = 8;
          }
          else if (tileLeftVal != 1 && tileUpVal == 1 &&
                   tileRightVal == 1 && tileDownVal != 1)
          {
            tu = 7;
          }
          else if (tileLeftVal == 1 && tileUpVal != 1 &&
                   tileRightVal != 1 && tileDownVal == 1)
          {
            tu = 6;
          }
          else if (tileLeftVal == 1 && tileUpVal != 1 &&
                   tileRightVal == 1 && tileDownVal != 1)
          {
            tu = 5;
          }
          else if (tileLeftVal == 1 && tileUpVal == 1 &&
                   tileRightVal != 1 && tileDownVal != 1)
          {
            tu = 4;
          }
          else if (tileLeftVal != 1 && tileUpVal != 1 &&
                   tileRightVal != 1 && tileDownVal == 1)
          {
            tu = 3;
          }
          else if (tileLeftVal != 1 && tileUpVal != 1 &&
                   tileRightVal == 1 && tileDownVal != 1)
          {
            tu = 2;
          }
          else if (tileLeftVal != 1 && tileUpVal == 1 &&
                   tileRightVal != 1 && tileDownVal != 1)
          {
            tu = 1;
          }
          else if (tileLeftVal == 1 && tileUpVal != 1 &&
                   tileRightVal != 1 && tileDownVal != 1)
          {
            tu = 0;
          }
          else
          {
            tv = 0;
          }
        }

        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        // Grass layer
        quad = &m_verticesGrassEdges[tileInMap * 4];

        quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
        quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
        quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

        tu = 3;
        tv = 0;
        if (tileValue != 0 &&
            (tileLeftVal == 0 || tileUpVal == 0 ||
             tileRightVal == 0 || tileDownVal == 0))
        {
          tv = 1;
          if (tileLeftVal == 0 && tileUpVal == 0 &&
              tileRightVal == 0 && tileDownVal == 0)
          {
            // Grass all around
            tu = 14;
          }
          else if (tileLeftVal == 0 && tileUpVal != 0 &
                   tileRightVal == 0 && tileDownVal == 0)
          {
            tu = 13;
          }
          else if (tileLeftVal != 0 && tileUpVal == 0 &&
                   tileRightVal == 0 && tileDownVal == 0)
          {
            tu = 12;
          }
          else if (tileLeftVal == 0 && tileUpVal == 0 &&
                   tileRightVal == 0 && tileDownVal != 0)
          {
            tu = 11;
          }
          else if (tileLeftVal == 0 && tileUpVal == 0 &&
                   tileRightVal != 0 && tileDownVal == 0)
          {
            tu = 10;
          }
          else if (tileLeftVal != 0 && tileUpVal != 0 &&
                   tileRightVal == 0 && tileDownVal == 0)
          {
            tu = 9;
          }
          else if (tileLeftVal != 0 && tileUpVal == 0 &&
                   tileRightVal != 0 && tileDownVal == 0)
          {
            tu = 8;
          }
          else if (tileLeftVal != 0 && tileUpVal == 0 &&
                   tileRightVal == 0 && tileDownVal != 0)
          {
            tu = 7;
          }
          else if (tileLeftVal == 0 && tileUpVal != 0 &&
                   tileRightVal != 0 && tileDownVal == 0)
          {
            tu = 6;
          }
          else if (tileLeftVal == 0 && tileUpVal != 0 &&
                   tileRightVal == 0 && tileDownVal != 0)
          {
            tu = 5;
          }
          else if (tileLeftVal == 0 && tileUpVal == 0 &&
                   tileRightVal != 0 && tileDownVal != 0)
          {
            tu = 4;
          }
          else if (tileLeftVal != 0 && tileUpVal != 0 &&
                   tileRightVal != 0 && tileDownVal == 0)
          {
            tu = 3;
          }
          else if (tileLeftVal != 0 && tileUpVal != 0 &&
                   tileRightVal == 0 && tileDownVal != 0)
          {
            tu = 2;
          }
          else if (tileLeftVal != 0 && tileUpVal == 0 &&
                   tileRightVal != 0 && tileDownVal != 0)
          {
            tu = 1;
          }
          else if (tileLeftVal == 0 && tileUpVal != 0 &&
                   tileRightVal != 0 && tileDownVal != 0)
          {
            tu = 0;
          }
          else
          {
            tv = 0;
          }
        }

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
  target.draw(m_verticesSandEdges, states);
  target.draw(m_verticesGrassEdges, states);
}

const sf::Vector2u World::tileSize() const
{
  return m_tileSize;
}

const sf::Uint32 World::mapHeight() const
{
  return m_mapHeight;
}

const sf::Uint32 World::mapWidth() const
{
  return m_mapWidth;
}

