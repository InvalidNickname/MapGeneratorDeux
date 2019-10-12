#include "R.h"

R &R::get() {
  static R s;
  return s;
}

R::R() {
  std::ifstream input("jsons/resources.json");
  Json base_file = Json::parse(input);
  input.close();
  Json unsigned_values = base_file.at("unsigned");
  for (const Json &i : unsigned_values) {
    unsigned_map.insert(pair(i.at(0), i.at(1)));
  }
}

uint16_t R::getUint(const string &name) const {
  return unsigned_map.at(name);
}
