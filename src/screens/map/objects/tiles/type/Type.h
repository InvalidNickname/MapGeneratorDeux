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
  Type(string type, string archtype, vector<string> name, Color biome_color, vector<Color> base_color,
       bool above_sea_level, int priority, pair<uint16_t, uint16_t> *temperature_range,
       pair<float, float> *moisture_range, const string &neighbour);

  [[nodiscard]] string getName(Level level) const;

  [[nodiscard]] Color getBiomeColor() const;

  [[nodiscard]] Color getBaseColor(Level level) const;

  [[nodiscard]] string getArchtype() const;

  [[nodiscard]] string getTypeName() const;

  [[nodiscard]] bool isAboveSeaLevel() const;

  [[nodiscard]] int getPriority() const;

  [[nodiscard]] const pair<uint16_t, uint16_t> *getTemperatureRange() const;

  [[nodiscard]] const pair<float, float> *getMoistureRange() const;

  [[nodiscard]] string getNeighbour() const;

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