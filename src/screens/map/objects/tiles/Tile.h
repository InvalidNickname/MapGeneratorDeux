#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

#include <utils/GenerationParameters.h>
#include <utils/Random.h>

#include "type/Type.h"
#include "type/Tileset.h"

using namespace sf;

class Tile {
 public:
  Tile(uint16_t x, uint16_t y);

  void render(RenderTarget *_target, MapMode mode, int16_t _x, int16_t _y, int max_z, int min_z);

  float getLatitude();

  float getLongitude();

  uint16_t getX();

  uint16_t getY();

  uint16_t getZ();

  Type *getType();

  void setLevel(Level _level);

  void setType(const string &type);

  void increaseZ(int z);

  void setZ(uint16_t _z);

  uint16_t getTemperature();

  void setTemperature(uint16_t temperature);

  float getMoisture();

  void setMoisture(float _moisture);

 private:
  uint16_t x, y, z{0};
  float latitude, longitude;
  float tile_x{0}, tile_y{0};
  float moisture{0};
  uint16_t temperature{0};
  Type *type{nullptr};
  Level level{Level::NO};
  VertexArray shape;

  void drawTile(RenderTarget *_target, Color color);
};