#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class AssetLoader {
 public:
  static AssetLoader &get();

  AssetLoader(AssetLoader const &) = delete;

  AssetLoader &operator=(AssetLoader const &) = delete;

  [[nodiscard]] Texture *getTexture(const string &name) const;

  [[nodiscard]] Font *getFont(const string &name) const;

 private:
  map<string, Texture *> texture_map;
  map<string, Font *> font_map;

  AssetLoader();

  ~AssetLoader() = default;

  void loadTexture(const string &pathname, const string &name, IntRect position = IntRect());

  void loadFont(const string &pathname, const string &name);

};
