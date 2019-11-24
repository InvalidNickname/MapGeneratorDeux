#ifndef MGD_GENERATOR_SRC_UTILS_RANDOM_H
#define MGD_GENERATOR_SRC_UTILS_RANDOM_H

#include <random>

/// @brief Генератор случайных чисел
class Random {
 public:
  static Random &Get() {
    static Random s;
    return s;
  }

  Random(Random const &) = delete;

  Random &operator=(Random const &) = delete;

  /**
   * Устанавливает сид генератора
   * @param seed Сид генератора
   */
  void SetSeed(uint32_t seed) {
    seed_ = seed;
    engine_ = std::default_random_engine{seed_};
  }

  /**
   * Возвращает случайное число в диапазоне от x до y
   * @param x Нижняя граница для числа
   * @param y Верхняя граница для числа
   * @return Случайное число от x до y
   */
  [[nodiscard]] int GetInt(int x, int y) {
    std::uniform_int_distribution<int> distribution(x, y);
    return distribution(engine_);
  }

  /**
   * Возвращает сид генератора
   * @return Сид генератора
   */
  [[nodiscard]] uint32_t GetSeed() const {
    return seed_;
  }

 private:
  uint32_t seed_{0}; ///< Сид генератора

  Random() = default;

  std::default_random_engine engine_;

  ~Random() = default;

};

#endif