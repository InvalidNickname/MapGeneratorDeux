#include "Type.h"

Type::Type(string t, string at, vector<string> n, Color bic, vector<Color> bac, bool asl, int priority,
           pair<uint16_t, uint16_t> *tr, pair<float, float> *mr, const string &neighbour)
    : type(move(t)), archtype(move(at)), name(move(n)), biome_color(bic), base_color(move(bac)),
      above_sea_level(asl), priority(priority), temperature_range(tr), moisture_range(mr),
      neighbour(neighbour) {}

string Type::getName(Level level) const {
  switch (level) {
    case NO:return name.at(3);
    case SMALL:return name.at(2);
    case MEDIUM:return name.at(1);
    case HIGH:return name.at(0);
  }
}

Color Type::getBiomeColor() const {
  return biome_color;
}

Color Type::getBaseColor(Level level) const {
  switch (level) {
    case NO:return base_color.at(3);
    case SMALL:return base_color.at(2);
    case MEDIUM:return base_color.at(1);
    case HIGH:return base_color.at(0);
  }
}

string Type::getArchtype() const {
  return archtype;
}

string Type::getTypeName() const {
  return type;
}

bool Type::isAboveSeaLevel() const {
  return above_sea_level;
}

int Type::getPriority() const {
  return priority;
}

const pair<uint16_t, uint16_t> *Type::getTemperatureRange() const {
  return temperature_range;
}

const pair<float, float> *Type::getMoistureRange() const {
  return moisture_range;
}

string Type::getNeighbour() const {
  return neighbour;
}
