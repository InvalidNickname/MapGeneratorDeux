#include "perlin_noise.h"

PerlinNoise::PerlinNoise(uint32_t seed) {
  perm_.resize(256);
  std::iota(perm_.begin(), perm_.end(), 0);
  std::default_random_engine engine(seed);
  std::shuffle(perm_.begin(), perm_.end(), engine);
  perm_.insert(perm_.end(), perm_.begin(), perm_.end());
}

float PerlinNoise::OctNoise(float x, float y, float px, float py) {
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

  t = Fade(fy0);
  s = Fade(fx0);

  nx0 = Grad(perm_[ix0 + perm_[iy0]], fx0, fy0);
  nx1 = Grad(perm_[ix0 + perm_[iy1]], fx0, fy1);
  n0 = Lerp(t, nx0, nx1);

  nx0 = Grad(perm_[ix1 + perm_[iy0]], fx1, fy0);
  nx1 = Grad(perm_[ix1 + perm_[iy1]], fx1, fy1);
  n1 = Lerp(t, nx0, nx1);

  return 0.507f * (Lerp(s, n0, n1));
}

float PerlinNoise::Noise(float x, float y, float px, float py, uint16_t oct) {
  float val = 0;
  for (int i = 0; i < oct; ++i) {
    val += pow(0.5f, i) * OctNoise(x * pow(2.f, i), y * pow(2.f, i), px * pow(2.f, i), py * pow(2.f, i));
  }
  return val;
}
