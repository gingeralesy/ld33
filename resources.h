#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

class Resources
{
public:
  static const std::string dataPath();
  static const std::string pngDataPath(const std::string &dataName);
};

#endif // RESOURCES_H
