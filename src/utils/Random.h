#pragma once

#include <random>

class Random {
  public:
    static Random &get() {
        static Random s;
        return s;
    }

    Random(Random const &) = delete;

    Random &operator=(Random const &) = delete;

    void setSeed(uint32_t _seed) {
        seed = _seed;
        engine = std::default_random_engine{seed};
    }

    int getInt(int x, int y) {
        std::uniform_int_distribution<int> distribution(x, y);
        return distribution(engine);
    }

    uint32_t getSeed() {
        return seed;
    }

  private:
    uint32_t seed{0};

    Random() = default;

    std::default_random_engine engine;

    ~Random() = default;

};