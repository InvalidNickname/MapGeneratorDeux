#pragma once

#include <SFML/Graphics.hpp>

#include "utils/GenerationParameters.h"
#include "type/Type.h"
#include "type/Tileset.h"

class Tile {
 public:
  Tile(uint16_t x, uint16_t y);

  void render(RenderTarget *_target, MapMode mode, int16_t _x, int16_t _y, int max_z, int min_z);

  [[nodiscard]] float getLatitude() const;

  [[nodiscard]] float getLongitude() const;

  [[nodiscard]] uint16_t getX() const;

  [[nodiscard]] uint16_t getY() const;

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
  const uint16_t x, y;
  uint16_t z{0};
  float latitude{}, longitude{};
  float tile_x{0}, tile_y{0};
  float moisture{0};
  uint16_t temperature{0};
  Type *type{nullptr};
  Level level{Level::NO};

 private:
  VertexArray shape;

  void drawTile(RenderTarget *_target, Color color);
};