#ifndef WORLD_H
#define WORLD_H

#include "entity.h"

class World : public Entity
{
public:
  explicit World(const std::string &dataName = "world");
};

#endif // WORLD_H
