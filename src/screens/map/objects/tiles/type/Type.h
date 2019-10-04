#pragma once

#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics/Color.hpp>

#include "Level.h"

using namespace std;
using namespace sf;

class Type {
  public:
    Type(string type, string archtype, vector<string> name, Color biomeColor, vector<Color> baseColor,
         bool aboveSeaLevel);

    string getName(Level level);

    Color getBiomeColor();

    Color getBaseColor(Level level);

    string getArchtype();

    string getTypeName();

    bool isAboveSeaLevel();

  private:
    const string type, archtype;
    const vector<string> name;
    const Color biomeColor;
    const vector<Color> baseColor;
    const bool aboveSeaLevel;

};