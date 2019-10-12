#include "Type.h"

Type::Type(string t, string at, vector<string> n, Color bic, vector<Color> bac, bool asl, int priority,
           pair<uint16_t, uint16_t> *tr, pair<float, float> *mr, string neighbour)
    : type(std::move(t)), archtype(std::move(at)), name(std::move(n)), biome_color(bic), base_color(std::move(bac)),
      above_sea_level(asl), priority(priority), temperature_range(tr), moisture_range(mr),
      neighbour(std::move(neighbour)) {}

string Type::getName(Level level) {
  switch (level) {
    case NO:return name.at(3);
    case SMALL:return name.at(2);
    case MEDIUM:return name.at(1);
    case HIGH:return name.at(0);
  }
}

Color Type::getBiomeColor() {
  return biome_color;
}

Color Type::getBaseColor(Level level) {
  switch (level) {
    case NO:return base_color.at(3);
    case SMALL:return base_color.at(2);
    case MEDIUM:return base_color.at(1);
    case HIGH:return base_color.at(0);
  }
}

string Type::getArchtype() {
  return archtype;
}

string Type::getTypeName() {
  return type;
}

bool Type::isAboveSeaLevel() {
  return above_sea_level;
}

int Type::getPriority() {
  return priority;
}

const pair<uint16_t, uint16_t> *Type::getTemperatureRange() {
  return temperature_range;
}

const pair<float, float> *Type::getMoistureRange() {
  return moisture_range;
}

string Type::getNeighbour() {
  return neighbour;
}
