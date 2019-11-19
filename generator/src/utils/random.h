#ifndef MGD_GENERATOR_SRC_UTILS_RANDOM_H
#define MGD_GENERATOR_SRC_UTILS_RANDOM_H

#include <random>

class Random {
 public:
  static Random &Get() {
    static Random s;
    return s;
  }

  Random(Random const &) = delete;

  Random &operator=(Random const &) = delete;

  void SetSeed(uint32_t _seed) {
    seed_ = _seed;
    engine_ = std::default_random_engine{seed_};
  }

  [[nodiscard]] int GetInt(int x, int y) {
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(engine_);
  }

  [[nodiscard]] uint32_t GetSeed() const {
    return seed_;
  }

 private:
  uint32_t seed_{0};

  Random() = default;

  std::default_random_engine engine_;

  ~Random() = default;

};

#endif