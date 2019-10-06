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

    void setSeed(long unsigned int _seed) {
        seed = _seed;
        engine = std::default_random_engine{seed};
    }

    int getInt(int x, int y) {
        std::uniform_int_distribution<int> distribution(x, y);
        return distribution(engine);
    }

    long unsigned int getSeed() {
        return seed;
    }

  private:
    long unsigned int seed{0};

    Random() = default;

    std::default_random_engine engine;

    ~Random() = default;

};