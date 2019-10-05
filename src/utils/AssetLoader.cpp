#include "AssetLoader.h"

AssetLoader &AssetLoader::get() {
    static AssetLoader s;
    return s;
}

AssetLoader::AssetLoader() {
    loadTexture("graphics/interface/map_mode_default.png", "map_mode_default_0", IntRect(0, 0, 41, 31));
    loadTexture("graphics/interface/map_mode_default.png", "map_mode_default_1", IntRect(41, 0, 41, 31));
    loadTexture("graphics/interface/map_mode_biomes.png", "map_mode_biomes_0", IntRect(0, 0, 41, 31));
    loadTexture("graphics/interface/map_mode_biomes.png", "map_mode_biomes_1", IntRect(41, 0, 41, 31));
    loadTexture("graphics/interface/map_mode_temperature.png", "map_mode_temperature_0", IntRect(0, 0, 41, 31));
    loadTexture("graphics/interface/map_mode_temperature.png", "map_mode_temperature_1", IntRect(41, 0, 41, 31));
    loadTexture("graphics/interface/minimap_background.png", "minimap_background");
    loadTexture("graphics/interface/minimap_overlay.png", "minimap_overlay");
}

Texture *AssetLoader::getTexture(const string &name) {
    return textureMap.at(name);
}

void AssetLoader::loadTexture(const string &pathname, const string &name, IntRect position) {
    auto texture = new Texture();
    texture->loadFromFile(pathname, position);
    texture->setSmooth(true);
    textureMap.insert(pair(name, texture));
}
