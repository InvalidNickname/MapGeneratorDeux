#include "asset_loader.h"

AssetLoader &AssetLoader::Get() {
  static AssetLoader s;
  return s;
}

AssetLoader::AssetLoader() {
  LoadTexture("interface/map_mode_default.png", "map_mode_default_0", {0, 0, 41, 31});
  LoadTexture("interface/map_mode_default.png", "map_mode_default_1", {41, 0, 41, 31});
  LoadTexture("interface/map_mode_biomes.png", "map_mode_biomes_0", {0, 0, 41, 31});
  LoadTexture("interface/map_mode_biomes.png", "map_mode_biomes_1", {41, 0, 41, 31});
  LoadTexture("interface/map_mode_temperature.png", "map_mode_temperature_0", {0, 0, 41, 31});
  LoadTexture("interface/map_mode_temperature.png", "map_mode_temperature_1", {41, 0, 41, 31});
  LoadTexture("interface/map_mode_height.png", "map_mode_height_0", {0, 0, 41, 31});
  LoadTexture("interface/map_mode_height.png", "map_mode_height_1", {41, 0, 41, 31});
  LoadTexture("interface/map_mode_moisture.png", "map_mode_moisture_0", {0, 0, 41, 31});
  LoadTexture("interface/map_mode_moisture.png", "map_mode_moisture_1", {41, 0, 41, 31});
  LoadTexture("interface/minimap_overlay.png", "minimap_overlay");
  LoadTexture("tiles/selected_tile.png", "selected_tile");
  LoadTexture("tiles/river_0.png", "river_straight");
  LoadTexture("tiles/river_2.png", "river_2");
  LoadTexture("tiles/river_3.png", "river_end");
  LoadTexture("tiles/river_4.png", "river_start");

  for (int i = -2; i < 3; i++) {
    LoadTexture("interface/settings_height.png",
                "s_height_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    LoadTexture("interface/settings_height.png",
                "s_height_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
    LoadTexture("interface/settings_temperature.png",
                "s_temperature_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    LoadTexture("interface/settings_temperature.png",
                "s_temperature_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
    LoadTexture("interface/settings_size.png",
                "s_size_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    LoadTexture("interface/settings_size.png",
                "s_size_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
    LoadTexture("interface/settings_flatness.png",
                "s_flatness_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    LoadTexture("interface/settings_flatness.png",
                "s_flatness_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
    LoadTexture("interface/settings_moisture.png",
                "s_moisture_" + to_string(i) + "_0",
                {(i + 2) * 140, 150, 140, 150});
    LoadTexture("interface/settings_moisture.png",
                "s_moisture_" + to_string(i) + "_1",
                {(i + 2) * 140, 0, 140, 150});
  }

  LoadTexture("interface/check.png", "check_0", {0, 0, 50, 50});
  LoadTexture("interface/check.png", "check_1", {50, 0, 50, 50});
  LoadTexture("interface/go.png", "go");

  LoadTexture("background/settings_background.png", "s_background");

  LoadFont("abel.ttf", "default");
}

Texture *AssetLoader::GetTexture(const string &name) const {
  return texture_map_.at(name);
}

void AssetLoader::LoadTexture(const string &pathname, const string &name, IntRect position) {
  auto texture = new Texture();
  if (texture->loadFromFile("graphics/" + pathname, position)) {
    texture->setSmooth(true);
    texture_map_.insert(pair(name, texture));
  }
}

Font *AssetLoader::GetFont(const string &name) const {
  return font_map_.at(name);
}

void AssetLoader::LoadFont(const string &pathname, const string &name) {
  auto font = new Font();
  if (font->loadFromFile("fonts/" + pathname)) {
    font_map_.insert(pair(name, font));
  }
}
