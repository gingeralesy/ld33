#include "resources.h"

const std::string Resources::dataPath()
{
  static const std::string path = "data/";
  return path;
}

const std::string Resources::pngDataPath(const std::string &dataName)
{
  const std::string path = dataPath() + dataName + ".png";
  return path;
}
