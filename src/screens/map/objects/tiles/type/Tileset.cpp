#include "screens/map/objects/tiles/type/Tileset.h"

Tileset &Tileset::get() {
    static Tileset s;
    return s;
}

Tileset::Tileset() {
    std::ifstream input("jsons/tiles.json");
    Json baseFile;
    input >> baseFile;
    baseFile = baseFile.at("data");
    // тип суши для генератора
    tileset.push_back(new Type("GenLand", "GenLand", vector<string>(), Color(), vector<Color>(), true));
    // тип воды для генератора
    tileset.push_back(new Type("GenWater", "GenWater", vector<string>(), Color(), vector<Color>(), false));
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
        tileset.push_back(new Type(type, archtype, name, biomeColor, baseColor, aboveSeaLevel));
    }
}

Type *Tileset::getType(const string &type) {
    for (Type *value : tileset) {
        if (value->getTypeName() == type) {
            return value;
        }
    }
    return nullptr;
}
