#include "animation.h"

Animation::Animation(sf::IntRect tileSize,
                     sf::Uint32 row, sf::Uint32 startCol,
                     const std::vector<float> &frameTimes)
  : m_tileSize(tileSize), m_row(row), m_firstFrame(startCol),
    m_frameTimes(frameTimes), m_curFrame(0), m_timePassed(0.f)
{
  for (sf::Uint32 i = 0; i < m_frameTimes.size(); i++)
  {
    sf::Uint32
        left = (m_firstFrame + i) * m_tileSize.width,
        top = m_row * m_tileSize.height;
    m_frames.push_back(sf::IntRect(left, top, m_tileSize.width,
                                   m_tileSize.height));
  }
}

Animation::~Animation()
{ }

const sf::IntRect Animation::getFrame(const float &delta)
{
  m_timePassed += delta;

  if (m_frameTimes.at(m_curFrame) <= m_timePassed)
  {
    m_curFrame += 1;
    m_timePassed = 0.f;

    if (m_curFrame >= m_frameTimes.size())
      m_curFrame = 0;
  }

  return m_frames.at(m_curFrame);
}
