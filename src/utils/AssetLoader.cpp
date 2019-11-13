#include "AssetLoader.h"

AssetLoader &AssetLoader::get() {
  static AssetLoader s;
  return s;
}

AssetLoader::AssetLoader() {
  loadTexture("interface/map_mode_default.png", "map_mode_default_0", {0, 0, 41, 31});
  loadTexture("interface/map_mode_default.png", "map_mode_default_1", {41, 0, 41, 31});
  loadTexture("interface/map_mode_biomes.png", "map_mode_biomes_0", {0, 0, 41, 31});
  loadTexture("interface/map_mode_biomes.png", "map_mode_biomes_1", {41, 0, 41, 31});
  loadTexture("interface/map_mode_temperature.png", "map_mode_temperature_0", {0, 0, 41, 31});
  loadTexture("interface/map_mode_temperature.png", "map_mode_temperature_1", {41, 0, 41, 31});
  loadTexture("interface/map_mode_height.png", "map_mode_height_0", {0, 0, 41, 31});
  loadTexture("interface/map_mode_height.png", "map_mode_height_1", {41, 0, 41, 31});
  loadTexture("interface/map_mode_moisture.png", "map_mode_moisture_0", {0, 0, 41, 31});
  loadTexture("interface/map_mode_moisture.png", "map_mode_moisture_1", {41, 0, 41, 31});
  loadTexture("interface/minimap_overlay.png", "minimap_overlay");
  loadTexture("tiles/selected_tile.png", "selected_tile");

  for (int i = -2; i < 3; i++) {
    loadTexture("interface/settings_height.png",
                "s_height_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    loadTexture("interface/settings_height.png",
                "s_height_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
    loadTexture("interface/settings_temperature.png",
                "s_temperature_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    loadTexture("interface/settings_temperature.png",
                "s_temperature_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
  }

  loadTexture("background/settings_background.png", "s_background");

  loadFont("abel.ttf", "default");
}

Texture *AssetLoader::getTexture(const string &name) const {
  return texture_map.at(name);
}

void AssetLoader::loadTexture(const string &pathname, const string &name, IntRect position) {
  auto texture = new Texture();
  if (texture->loadFromFile("graphics/" + pathname, position)) {
    texture->setSmooth(true);
    texture_map.insert(pair(name, texture));
  }
}

Font *AssetLoader::getFont(const string &name) const {
  return font_map.at(name);
}

void AssetLoader::loadFont(const string &pathname, const string &name) {
  auto font = new Font();
  if (font->loadFromFile("fonts/" + pathname)) {
    font_map.insert(pair(name, font));
  }
}
