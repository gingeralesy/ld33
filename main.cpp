#include "game.h"

int main()
{
  Game g("LD33");
  if (g.init())
    return g.exec();
  return EXIT_FAILURE;
}
