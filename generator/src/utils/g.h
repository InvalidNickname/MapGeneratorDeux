#ifndef MGD_GENERATOR_SRC_UTILS_G_H
#define MGD_GENERATOR_SRC_UTILS_G_H

#include <cmath>
#include <utility>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct G {
 public:
  static void SetIndex(map<string, string> index) { Get().index_ = move(index); }

  G(G const &) = delete;

  G &operator=(G const &) = delete;

  [[nodiscard]] static uint16_t GetMaxTemp() {
    return temperature_[stoi(Get().index_["temperature"])] + 30;
  }

  [[nodiscard]] static uint16_t GetMinTemp() {
    return temperature_[stoi(Get().index_["temperature"])] - 30;
  }

  [[nodiscard]] static float GetMaxMoisture() {
    float moisture = moisture_[stoi(Get().index_["moisture"])] + 0.5f;
    if (moisture > 1) moisture = 1;
    return moisture;
  }

  [[nodiscard]] static float GetMinMoisture() {
    float moisture = moisture_[stoi(Get().index_["moisture"])] - 0.5f;
    if (moisture < 0) moisture = 0;
    return moisture;
  }

  [[nodiscard]] static uint16_t GetMapH() {
    return map_size_[stoi(Get().index_["size"])].second;
  }

  [[nodiscard]] static uint16_t GetMapW() {
    return map_size_[stoi(Get().index_["size"])].first;
  }

  [[nodiscard]] static float GetOceanLevel() {
    return ocean_level_[stoi(Get().index_["ocean_level"])];
  }
  [[nodiscard]] static uint8_t GetFlatness() {
    return flatness_[stoi(Get().index_["flatness"])];
  }

  [[nodiscard]] static string GetGeneratorType() {
    return Get().index_["generator"];
  }

 private:
  map<string, string> index_;

  constexpr static pair<uint16_t, uint16_t> map_size_[5] = {{150, 95}, {200, 127}, {300, 190}, {450, 285}, {600, 380}};
  constexpr static uint16_t temperature_[5] = {253, 273, 293, 313, 333}; // +-30
  constexpr static float ocean_level_[5] = {0.8, 1, 1.08, 1.2, 1.3};
  constexpr static uint8_t flatness_[5] = {0, 1, 2, 3, 4};
  constexpr static float moisture_[5] = {0, 0.25, 0.5, 0.75, 1}; // +-0.5

  G() = default;

  ~G() = default;

  static G &Get() {
    static G s;
    return s;
  }
};

#endif