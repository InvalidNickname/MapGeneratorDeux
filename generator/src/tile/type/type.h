#ifndef MGD_GENERATOR_SRC_TILE_TYPE_TYPE_H
#define MGD_GENERATOR_SRC_TILE_TYPE_TYPE_H

#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics/Color.hpp>

#include "level.h"

using namespace std;
using namespace sf;

struct Type {
 public:
  const string type_name, archtype;
  const Color biome_color;
  // информация для генерации
  const bool above_sea_level;
  const int priority;
  const pair<uint16_t, uint16_t> *temperature_range;
  const pair<float, float> *moisture_range;
  const string neighbour;

  Type(string t, string at, vector<string> n, Color bic, vector<Color> bac, bool asl, int priority,
       pair<uint16_t, uint16_t> *tr, pair<float, float> *mr, const string &neighbour)
      : type_name(move(t)), archtype(move(at)), name(move(n)), biome_color(bic), base_color(move(bac)),
        above_sea_level(asl), priority(priority), temperature_range(tr), moisture_range(mr),
        neighbour(neighbour) {}

  [[nodiscard]] string GetName(Level level) const;

  [[nodiscard]] Color GetBaseColor(Level level) const;

 private:
  const vector<Color> base_color;
  const vector<string> name;
};

#endif