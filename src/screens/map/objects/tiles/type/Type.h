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
  Type(string type, string archtype, vector<string> name, Color biome_color, vector<Color> base_color,
       bool above_sea_level, int priority, pair<uint16_t, uint16_t> *temperature_range,
       pair<float, float> *moisture_range,
       string neighbour);

  string getName(Level level);

  Color getBiomeColor();

  Color getBaseColor(Level level);

  string getArchtype();

  string getTypeName();

  bool isAboveSeaLevel();

  int getPriority();

  const pair<uint16_t, uint16_t> *getTemperatureRange();

  const pair<float, float> *getMoistureRange();

  string getNeighbour();

 private:
  const string type, archtype;
  const vector<string> name;
  const Color biome_color;
  const vector<Color> base_color;
  // информация для генерации
  const bool above_sea_level;
  const int priority;
  const pair<uint16_t, uint16_t> *temperature_range;
  const pair<float, float> *moisture_range;
  const string neighbour;

};