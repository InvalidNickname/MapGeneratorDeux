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

    void setSeed(int seed) {
        engine = std::default_random_engine{static_cast<long unsigned int>(seed)};
    }

    int getInt(int x, int y) {
        std::uniform_int_distribution<int> distribution(x, y);
        return distribution(engine);
    }

  private:
    Random() = default;

    std::default_random_engine engine;

    ~Random() = default;

};