#ifndef MGD_GENERATOR_SRC_TILE_TILE_H
#define MGD_GENERATOR_SRC_TILE_TILE_H

#include <SFML/System.hpp>

#include "tile/type/tileset.h"

class Tile {
 public:
  const Vector2u pos_;
  const float latitude_, longitude_;

  explicit Tile(Vector2u pos);

  [[nodiscard]] uint16_t GetZ() const;

  [[nodiscard]] Type *GetType() const;

  void SetLevel(Level level);

  void SetType(const string &type);

  void IncreaseZ(int z);

  void SetZ(uint16_t z);

  [[nodiscard]] uint16_t GetTemperature() const;

  void SetTemperature(uint16_t temperature);

  [[nodiscard]] float GetMoisture() const;

  void SetMoisture(float moisture);

  [[nodiscard]] Level GetLevel() const;

 private:
  uint16_t z_{0};
  float moisture_{0};
  uint16_t temperature_{0};
  Type *type_{nullptr};
  Level level_{Level::NO};
};

#endif