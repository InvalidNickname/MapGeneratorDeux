#pragma once

#include <vector>
#include <numeric>
#include <random>

class PerlinNoise {
 public:
  explicit PerlinNoise(uint32_t seed);

  float noise(float x, float y, float px, float py, uint16_t oct = 1);

 private:
  std::vector<int> p;

  float octNoise(float x, float y, float px, float py);

  static inline float fade(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
  }

  static inline float lerp(float t, float a, float b) {
    return a + t * (b - a);
  }

  static float inline grad(uint32_t hash, float x, float y) {
    uint32_t h = hash & 7;      // Convert low 3 bits of hash code
    float u = h < 4 ? x : y;  // into 8 simple gradient directions,
    float v = h < 4 ? y : x;  // and compute the dot product with (x,y).
    return ((h & 1u) ? -u : u) + ((h & 2u) ? -2.f * v : 2.f * v);
  }

};
