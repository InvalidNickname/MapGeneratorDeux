#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(uint32_t seed) {
  p.resize(256);
  std::iota(p.begin(), p.end(), 0);
  std::default_random_engine engine(seed);
  std::shuffle(p.begin(), p.end(), engine);
  p.insert(p.end(), p.begin(), p.end());
}

float PerlinNoise::octNoise(float x, float y, float px, float py) {
  uint32_t ix0, iy0, ix1, iy1;
  float fx0, fy0, fx1, fy1;
  float s, t, nx0, nx1, n0, n1;

  ix0 = floor(x);
  iy0 = floor(y);
  fx0 = fmod(x, 1.f);
  fy0 = fmod(y, 1.f);
  fx1 = fx0 - 1.0f;
  fy1 = fy0 - 1.0f;
  ix1 = fmod(fmod(ix0 + 1.f, px), 255);
  iy1 = fmod(fmod(iy0 + 1.f, py), 255);
  ix0 = fmod(fmod(ix0, px), 255);
  iy0 = fmod(fmod(iy0, py), 255);

  t = fade(fy0);
  s = fade(fx0);

  nx0 = grad(p[ix0 + p[iy0]], fx0, fy0);
  nx1 = grad(p[ix0 + p[iy1]], fx0, fy1);
  n0 = lerp(t, nx0, nx1);

  nx0 = grad(p[ix1 + p[iy0]], fx1, fy0);
  nx1 = grad(p[ix1 + p[iy1]], fx1, fy1);
  n1 = lerp(t, nx0, nx1);

  return 0.507f * (lerp(s, n0, n1));
}

float PerlinNoise::noise(float x, float y, float px, float py, uint16_t oct) {
  float val = 0;
  for (int i = 0; i < oct; ++i) {
    val += pow(0.5f, i) * octNoise(x * pow(2.f, i), y * pow(2.f, i), px * pow(2.f, i), py * pow(2.f, i));
  }
  return val;
}
