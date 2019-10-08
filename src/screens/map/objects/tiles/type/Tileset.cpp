#include "Tileset.h"

#include <iostream>

Tileset::Tileset() {
    std::ifstream input("jsons/tiles.json");
    Json baseFile = Json::parse(input);
    baseFile = baseFile.at("data");
    // тип суши для генератора
    tileset.push_back(
            new Type("GenLand", "GenLand", vector<string>(), Color::Green, vector<Color>(4, Color::Green), true, 0,
                     new pair{TEMPERATURE_MIN, TEMPERATURE_MAX}, new pair{0.f, 1.f}, "nullptr"));
    // тип воды для генератора
    tileset.push_back(
            new Type("GenWater", "GenWater", vector<string>(), Color::Blue, vector<Color>(4, Color::Blue), false, 0,
                     new pair{TEMPERATURE_MIN, TEMPERATURE_MAX}, new pair{0.f, 1.f}, "nullptr"));
    for (Json temp : baseFile) {
        Json colorValue = temp.at("color");
        Json nameValue = temp.at("name");
        Json genInfo = temp.at("generator_info");
        string type = temp.at("type");
        string archtype = temp.at("archtype");
        vector<string> name;
        for (auto &i : nameValue) {
            name.push_back(i);
        }
        string biomeColorSt = colorValue.at("biome");
        Color biomeColor = Color(stoi(biomeColorSt.substr(2, 2), nullptr, 16),
                                 stoi(biomeColorSt.substr(4, 2), nullptr, 16),
                                 stoi(biomeColorSt.substr(6, 2), nullptr, 16));
        vector<Color> baseColor;
        for (auto &i : colorValue.at("base")) {
            string color = i;
            baseColor.emplace_back(stoi(color.substr(2, 2), nullptr, 16),
                                   stoi(color.substr(4, 2), nullptr, 16),
                                   stoi(color.substr(6, 2), nullptr, 16));
        }
        bool aboveSeaLevel = genInfo.at("above_sea_level");
        int priority = genInfo.at("priority");
        auto *temperatureRange = new pair{TEMPERATURE_MIN, TEMPERATURE_MAX};
        if (genInfo.contains("temp_min")) temperatureRange->first = genInfo.at("temp_min");
        if (genInfo.contains("temp_max")) temperatureRange->second = genInfo.at("temp_max");
        auto *moistureRange = new pair{0.f, 1.f};
        if (genInfo.contains("moisture_min")) moistureRange->first = genInfo.at("moisture_min");
        if (genInfo.contains("moisture_max")) moistureRange->second = genInfo.at("moisture_max");
        string neighbour = string();
        if (genInfo.contains("neighbour")) neighbour = genInfo.at("neighbour");
        tileset.push_back(
                new Type(type, archtype, name, biomeColor, baseColor, aboveSeaLevel, priority, temperatureRange,
                         moistureRange, neighbour));
    }
    // сортировка тайлсета по приоритету генерации
    sort(tileset.begin(), tileset.end(), [](Type *type1, Type *type2) -> bool {
        return type1->getPriority() < type2->getPriority();
    });
}

Tileset &Tileset::get() {
    static Tileset s;
    return s;
}

Type *Tileset::getType(const string &type) {
    for (Type *value : tileset) {
        if (value->getTypeName() == type) {
            return value;
        }
    }
    return nullptr;
}

uint16_t Tileset::getSize() {
    return tileset.size();
}

Type *Tileset::getType(const uint16_t &index) {
    return tileset.at(index);
}