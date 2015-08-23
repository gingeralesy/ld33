#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
public:
  explicit Animation(sf::IntRect tileSize,
                     sf::Uint32 row, sf::Uint32 startCol,
                     const std::vector<float> &frameTimes);
  ~Animation();

  const sf::IntRect getFrame(const float &delta);

private:
  sf::IntRect m_tileSize;
  sf::Uint32 m_row;
  sf::Uint32 m_firstFrame;
  std::vector<float> m_frameTimes;
  sf::Uint32 m_curFrame;
  float m_timePassed;
  std::vector<sf::IntRect> m_frames;
};

#endif // ANIMATION_H
