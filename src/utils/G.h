#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <map>
#include <string>

#include <iostream>

using namespace std;

class G {
 public:
  static constexpr float TILE_HEIGHT = 80.f;
  static constexpr float TILE_WIDTH = 69.282032302755091741097853660235f;

  static void setIndex(map<string, int16_t> _index) {
    get().index = move(_index);
  }

  G(G const &) = delete;

  G &operator=(G const &) = delete;

  [[nodiscard]] static uint16_t getMaxTemp() {
    return get().temperature[get().index["temperature"]] + 30;
  }

  [[nodiscard]] static uint16_t getMinTemp() {
    return get().temperature[get().index["temperature"]] - 30;
  }

  [[nodiscard]] static uint16_t getMapH() {
    return get().map_size[get().index["size"]].second;
  }

  [[nodiscard]] static uint16_t getMapW() {
    return get().map_size[get().index["size"]].first;
  }

  [[nodiscard]] static float getOceanLevel() {
    return get().ocean_level[get().index["ocean_level"]];
  }

  [[nodiscard]] static uint16_t getLandBorder() {
    return (uint16_t) (0.07f * (float) getMapH());
  }

 private:
  map<string, int16_t> index;

  const vector<pair<uint16_t, uint16_t>> map_size{{150, 95}, {200, 127}, {300, 190}, {450, 285}, {600, 380}};
  const vector<uint16_t> temperature{253, 273, 293, 313, 333}; // +-30
  const vector<float> ocean_level{0.8, 1, 1.08, 1.2, 1.3};

  G() = default;

  ~G() = default;

  static G &get() {
    static G s;
    return s;
  }
};