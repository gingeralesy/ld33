#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
  explicit Player(const std::string dataName = "player");
  ~Player();

  void doEvent(const sf::Event &event);
  void update(const float &delta);
};

#endif // PLAYER_H
