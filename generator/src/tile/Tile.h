#pragma once

#include <SFML/Graphics.hpp>

#include "type/Tileset.h"
#include "utils/MapMode.h"

class Tile {
 public:
  const Vector2u pos;

  explicit Tile(Vector2u pos);

  void render(RenderTarget *_target, MapMode mode, Vector2i pos, int max_z, int min_z);

  [[nodiscard]] float getLatitude() const;

  [[nodiscard]] float getLongitude() const;

  [[nodiscard]] uint16_t getZ() const;

  [[nodiscard]] Type *getType() const;

  void setLevel(Level _level);

  void setType(const string &type);

  void increaseZ(int z);

  void setZ(uint16_t _z);

  [[nodiscard]] uint16_t getTemperature() const;

  void setTemperature(uint16_t temperature);

  [[nodiscard]] float getMoisture() const;

  void setMoisture(float _moisture);

  [[nodiscard]] Level GetLevel() const;

 private:
  uint16_t z{0};
  float latitude{}, longitude{};
  Vector2f render_pos{0.f, 0.f};
  float moisture{0};
  uint16_t temperature{0};
  Type *type{nullptr};
  Level level{Level::NO};

 private:
  VertexArray shape;

  void drawTile(RenderTarget *_target, Color color);
};