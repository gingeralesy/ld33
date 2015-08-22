#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
  explicit Player(Game *game, const std::string dataName = "player");
  ~Player();

  void doEvent(const sf::Event &event);
  void update(const float &delta);

private:
  void keyPressed(const sf::Keyboard::Key &key);
  void keyReleased(const sf::Keyboard::Key &key);

};

#endif // PLAYER_H
