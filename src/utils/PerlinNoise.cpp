#include "PerlinNoise.h"

PerlinNoise::PerlinNoise(long unsigned int seed) {
    p.resize(256);
    std::iota(p.begin(), p.end(), 0);
    std::default_random_engine engine(seed);
    std::shuffle(p.begin(), p.end(), engine);
    p.insert(p.end(), p.begin(), p.end());
}

float PerlinNoise::noise(float x, float y, float z) {
    int _x = (int) floor(x) % 255;
    int _y = (int) floor(y) % 255;
    int _z = (int) floor(z) % 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    float u = fade(x);
    float v = fade(y);
    float w = fade(z);
    int A = p[_x] + _y;
    int AA = p[A] + _z;
    int AB = p[A + 1] + _z;
    int B = p[_x + 1] + _y;
    int BA = p[B] + _z;
    int BB = p[B + 1] + _z;
    float res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
                             lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
                     lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
                          lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
    return (res + 1.f) / 2.f;
}