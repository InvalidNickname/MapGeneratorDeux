#pragma once

#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics/Color.hpp>

#include <utils/GenerationParameters.h>

#include "Level.h"

using namespace std;
using namespace sf;

class Type {
  public:
    Type(string type, string archtype, vector<string> name, Color biomeColor, vector<Color> baseColor,
         bool aboveSeaLevel, int priority, pair<int, int> *temperatureRange, pair<float, float> *moistureRange,
         string neighbour);

    string getName(Level level);

    Color getBiomeColor();

    Color getBaseColor(Level level);

    string getArchtype();

    string getTypeName();

    bool isAboveSeaLevel();

    int getPriority();

    const pair<int, int> *getTemperatureRange();

    const pair<float, float> *getMoistureRange();

    string getNeighbour();

  private:
    const string type, archtype;
    const vector<string> name;
    const Color biomeColor;
    const vector<Color> baseColor;
    // информация для генерации
    const bool aboveSeaLevel;
    const int priority;
    const pair<int, int> *temperatureRange;
    const pair<float, float> *moistureRange;
    const string neighbour;

};