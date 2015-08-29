#ifndef UTIL_H
#define UTIL_H

#include <SFML/System.hpp>

class Util
{
public:
  static double dotProduct(const sf::Vector2f &a, const sf::Vector2f &b);
  static bool linesCollide(const sf::Vector2f &a1, const sf::Vector2f &a2,
                           const sf::Vector2f &b1, const sf::Vector2f &b2,
                           sf::Vector2f *out = 0);
  static double perpDotProduct(const sf::Vector2f &a, const sf::Vector2f &b);
};

#endif // UTIL_H
