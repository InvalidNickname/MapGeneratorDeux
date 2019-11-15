#pragma once

#include <cmath>
#include <utility>
#include <vector>
#include <map>
#include <string>

#include <iostream>

using namespace std;

struct G {
 public:
  static void SetIndex(map<string, int16_t> index) { Get().index_ = move(index); }

  G(G const &) = delete;

  G &operator=(G const &) = delete;

  [[nodiscard]] static uint16_t GetMaxTemp() {
    return temperature_[Get().index_["temperature"]] + 30;
  }

  [[nodiscard]] static uint16_t GetMinTemp() {
    return temperature_[Get().index_["temperature"]] - 30;
  }

  [[nodiscard]] static uint16_t GetMapH() {
    return map_size_[Get().index_["size"]].second;
  }

  [[nodiscard]] static uint16_t GetMapW() {
    return map_size_[Get().index_["size"]].first;
  }

  [[nodiscard]] static float GetOceanLevel() {
    return ocean_level_[Get().index_["ocean_level"]];
  }

  [[nodiscard]] static uint16_t GetLandBorder() {
    return 0.07f * GetMapH();
  }

 private:
  map<string, int16_t> index_;

  constexpr static pair<uint16_t, uint16_t> map_size_[5] = {{150, 95}, {200, 127}, {300, 190}, {450, 285}, {600, 380}};
  constexpr static uint16_t temperature_[5] = {253, 273, 293, 313, 333}; // +-30
  constexpr static float ocean_level_[5] = {0.8, 1, 1.08, 1.2, 1.3};

  G() = default;

  ~G() = default;

  static G &Get() {
    static G s;
    return s;
  }
};