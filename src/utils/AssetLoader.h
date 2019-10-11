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

  Texture *getTexture(const string &name);

 private:
  map<string, Texture *> textureMap;

  AssetLoader();

  ~AssetLoader() = default;

  void loadTexture(const string &pathname, const string &name, IntRect position = IntRect());

};
