#include "orcvillagegame.h"

int main()
{
  OrcVillageGame g;
  if (g.init())
    return g.exec();
  return EXIT_FAILURE;
}
