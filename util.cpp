#include "util.h"

double Util::dotProduct(const sf::Vector2f &a, const sf::Vector2f &b)
{
  return (a.x * b.x) + (a.y * b.y);
}

bool Util::linesCollide(const sf::Vector2f &a1, const sf::Vector2f &a2,
                        const sf::Vector2f &b1, const sf::Vector2f &b2,
                        sf::Vector2f *out)
{
  sf::Vector2f a(a2 - a1);
  sf::Vector2f b(b2 - b1);

  double p = perpDotProduct(a, b);
  if (!p) // parallel
    return false;

  sf::Vector2f c(b2 - a2);

  double aa = perpDotProduct(a, c);
  double bb = perpDotProduct(b, c);

  if (p < 0)
  {
    if (aa > 0)
      return false;
    if (bb > 0)
      return false;
    if (aa < p)
      return false;
    if (bb < p)
      return false;
  }
  else
  {
    if (aa < 0)
      return false;
    if (bb < 0)
      return false;
    if (aa > p)
      return false;
    if (bb > p)
      return false;
  }

  if (out)
  {
    sf::Vector2f bt(b2 - b1);
    double d = 1.0 - (aa / p);
    bt.x *= d;
    bt.y *= d;
    *out = sf::Vector2f(bt + b1); // intersection
  }
  return true;
}

double Util::perpDotProduct(const sf::Vector2f &a, const sf::Vector2f &b)
{
  return (a.y * b.x) - (a.x * b.y);
}
