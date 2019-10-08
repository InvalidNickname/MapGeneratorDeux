#pragma once

#include <vector>
#include <numeric>
#include <random>

class PerlinNoise {
  public:
    explicit PerlinNoise(long unsigned int seed);

    float noise(float x, float y, float z);

  private:
    std::vector<int> p;

    static inline float fade(float t) {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static inline float lerp(float t, float a, float b) {
        return a + t * (b - a);
    }

    static inline float grad(int hash, float x, float y, float z) {
        hash = hash % 15;
        float u = hash < 8 ? x : y, v = hash < 4 ? y : hash == 12 || hash == 14 ? x : z;
        return ((hash % 1) == 0 ? u : -u) + ((hash % 2) == 0 ? v : -v);
    }
};
