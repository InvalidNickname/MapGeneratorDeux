#ifndef MGD_GENERATOR_SRC_UTILS_G_H
#define MGD_GENERATOR_SRC_UTILS_G_H

#include <cmath>
#include <utility>
#include <vector>
#include <map>
#include <string>

using namespace std;

/// @brief Структура для хранения настроек генерации
struct G {
 public:
  /**
   * Установка настроек
   * @param index Map с настройками
   */
  static void SetIndex(map<string, string> index) { Get().index_ = move(index); }

  G(G const &) = delete;

  G &operator=(G const &) = delete;

  /**
   * Возвращает максимальную температуру карты
   * @return Максимальная температура карты
   */
  [[nodiscard]] static uint16_t GetMaxTemp() {
    return temperature_[stoi(Get().index_["temperature"])] + 30;
  }

  /**
   * Возвращает минимальную температуру карты
   * @return Минимальная температура карты
   */
  [[nodiscard]] static uint16_t GetMinTemp() {
    return temperature_[stoi(Get().index_["temperature"])] - 30;
  }

  /**
   * Возвращает максимальную влажность карты
   * @return Максимальная влажность карты
   */
  [[nodiscard]] static float GetMaxMoisture() {
    float moisture = moisture_[stoi(Get().index_["moisture"])] + 0.5f;
    if (moisture > 1) moisture = 1;
    return moisture;
  }

  /**
   * Возвращает минимальную влажность карты
   * @return Минимальная влажность карты
   */
  [[nodiscard]] static float GetMinMoisture() {
    float moisture = moisture_[stoi(Get().index_["moisture"])] - 0.5f;
    if (moisture < 0) moisture = 0;
    return moisture;
  }

  /**
   * Возвращает высоту карты
   * @return Высота карты
   */
  [[nodiscard]] static uint16_t GetMapH() {
    return map_size_[stoi(Get().index_["size"])].second;
  }

  /**
   * Возвращает ширину карты
   * @return Ширина карты
   */
  [[nodiscard]] static uint16_t GetMapW() {
    return map_size_[stoi(Get().index_["size"])].first;
  }

  /**
   * Возвращает уровень моря
   * @return Уровень моря
   */
  [[nodiscard]] static float GetOceanLevel() {
    return ocean_level_[stoi(Get().index_["ocean_level"])];
  }

  /**
   * Возвращает степень сглаживания карты
   * @return Степерь сглаживания карты
   */
  [[nodiscard]] static uint8_t GetFlatness() {
    return flatness_[stoi(Get().index_["flatness"])];
  }

  /**
   * Возвращает тип генератора
   * @return Тип генератора
   */
  [[nodiscard]] static string GetGeneratorType() {
    return Get().index_["generator"];
  }

 private:
  map<string, string> index_; ///< Настройки карты

  /// @brief Пары значений размеров карты для каждого варианта настроек
  constexpr static pair<uint16_t, uint16_t> map_size_[5] = {{150, 95}, {200, 127}, {300, 190}, {450, 285}, {600, 380}};
  /// @brief Значения температуры для каждого варианта настроек. Максимальная и минимальная температуры определяются как данная +-30
  constexpr static uint16_t temperature_[5] = {253, 273, 293, 313, 333}; // +-30
  /// @brief Значения уровня моря для каждого варианта настроек. При 0 моря нет вообще
  constexpr static float ocean_level_[5] = {0.8f, 1.f, 1.08f, 1.2f, 1.3f};
  /// @brief Значения степени сглаживания каждого варианта настроек. При генерации FlattenTerrain() вызывается столько раз, сколько указано тут
  constexpr static uint8_t flatness_[5] = {0, 1, 2, 3, 4};
  /// @brief Значения влажности для каждого варианта настроек. Максимальная и минимальная влажность определяются как данная +-0,5
  constexpr static float moisture_[5] = {0.f, 0.25f, 0.5f, 0.75f, 1.f}; // +-0.5

  G() = default;

  ~G() = default;

  static G &Get() {
    static G s;
    return s;
  }
};

#endif