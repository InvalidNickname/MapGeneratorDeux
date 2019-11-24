#ifndef MGD_GENERATOR_SRC_UTILS_PERLIN_NOISE_H
#define MGD_GENERATOR_SRC_UTILS_PERLIN_NOISE_H

#include <vector>
#include <numeric>
#include <random>

/// @brief Шум Перлина
class PerlinNoise {
 public:
  explicit PerlinNoise(uint32_t seed);

  /**
   * Возвращает шум для указанных параметров
   * @param x Координаты шума
   * @param y Координаты шума
   * @param px Период шума по x
   * @param py Период шума по y
   * @param oct Количество октав шума
   * @return
   */
  float Noise(float x, float y, float px, float py, uint16_t oct = 1);

 private:
  std::vector<int> perm_;

  float OctNoise(float x, float y, float px, float py);

  static inline float Fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  static inline float Lerp(float t, float a, float b) {
    return a + t * (b - a);
  }

  static float inline Grad(uint32_t hash, float x, float y) {
    uint32_t h = hash & 7u;
    float u = h < 4 ? x : y;
    float v = h < 4 ? y : x;
    return ((h & 1u) ? -u : u) + ((h & 2u) ? -2.f * v : 2.f * v);
  }
};

#endif
