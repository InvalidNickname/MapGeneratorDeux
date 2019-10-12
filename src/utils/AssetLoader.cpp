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
  loadTexture("graphics/interface/map_mode_height.png", "map_mode_height_0", IntRect(0, 0, 41, 31));
  loadTexture("graphics/interface/map_mode_height.png", "map_mode_height_1", IntRect(41, 0, 41, 31));
  loadTexture("graphics/interface/map_mode_moisture.png", "map_mode_moisture_0", IntRect(0, 0, 41, 31));
  loadTexture("graphics/interface/map_mode_moisture.png", "map_mode_moisture_1", IntRect(41, 0, 41, 31));
  loadTexture("graphics/interface/minimap_overlay.png", "minimap_overlay");
  loadTexture("graphics/tiles/selected_tile.png", "selected_tile");
}

Texture *AssetLoader::getTexture(const string &name) {
  return texture_map.at(name);
}

void AssetLoader::loadTexture(const string &pathname, const string &name, IntRect position) {
  auto texture = new Texture();
  texture->loadFromFile(pathname, position);
  texture->setSmooth(true);
  texture_map.insert(pair(name, texture));
}
