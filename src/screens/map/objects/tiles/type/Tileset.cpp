#include "Tileset.h"

Tileset::Tileset() {
  std::ifstream input("jsons/tiles.json");
  Json base_file = Json::parse(input);
  input.close();
  base_file = base_file.at("data");
  // тип суши для генератора
  tileset.push_back(
      new Type("GenLand", "GenLand", vector<string>(), Color::Green, vector<Color>(4, Color::Green), true, 0,
               new pair{TEMPERATURE_MIN, TEMPERATURE_MAX}, new pair{0.f, 1.f}, "nullptr"));
  // тип воды для генератора
  tileset.push_back(
      new Type("GenWater", "GenWater", vector<string>(), Color::Blue, vector<Color>(4, Color::Blue), false, 0,
               new pair{TEMPERATURE_MIN, TEMPERATURE_MAX}, new pair{0.f, 1.f}, "nullptr"));
  for (Json temp : base_file) {
    Json color_value = temp.at("color");
    Json name_value = temp.at("name");
    Json gen_info = temp.at("generator_info");
    string type = temp.at("type");
    string archtype = temp.at("archtype");
    vector<string> name;
    for (auto &i : name_value) {
      name.push_back(i);
    }
    string s_biome_color = color_value.at("biome");
    Color biome_color = Color(stoi(s_biome_color.substr(2, 2), nullptr, 16),
                              stoi(s_biome_color.substr(4, 2), nullptr, 16),
                              stoi(s_biome_color.substr(6, 2), nullptr, 16));
    vector<Color> base_color;
    for (auto &i : color_value.at("base")) {
      string color = i;
      base_color.emplace_back(stoi(color.substr(2, 2), nullptr, 16),
                              stoi(color.substr(4, 2), nullptr, 16),
                              stoi(color.substr(6, 2), nullptr, 16));
    }
    bool above_sea_level = gen_info.at("above_sea_level");
    int priority = gen_info.at("priority");
    auto *temperature_range = new pair{TEMPERATURE_MIN, TEMPERATURE_MAX};
    if (gen_info.contains("temp_min")) temperature_range->first = gen_info.at("temp_min");
    if (gen_info.contains("temp_max")) temperature_range->second = gen_info.at("temp_max");
    auto *moisture_range = new pair{0.f, 1.f};
    if (gen_info.contains("moisture_min")) moisture_range->first = gen_info.at("moisture_min");
    if (gen_info.contains("moisture_max")) moisture_range->second = gen_info.at("moisture_max");
    string neighbour = string();
    if (gen_info.contains("neighbour")) neighbour = gen_info.at("neighbour");
    tileset.push_back(
        new Type(type, archtype, name, biome_color, base_color, above_sea_level, priority, temperature_range,
                 moisture_range, neighbour));
  }
  // сортировка тайлсета по приоритету генерации
  sort(tileset.begin(), tileset.end(), [](Type *type1, Type *type2) -> bool {
    return type1->priority < type2->priority;
  });
}

Tileset &Tileset::get() {
  static Tileset s;
  return s;
}

Type *Tileset::getType(const string &type) const {
  for (Type *value : tileset) {
    if (value->type_name == type) {
      return value;
    }
  }
  return nullptr;
}

uint16_t Tileset::getSize() const {
  return tileset.size();
}

Type *Tileset::getType(const uint16_t &index) const {
  return tileset.at(index);
}