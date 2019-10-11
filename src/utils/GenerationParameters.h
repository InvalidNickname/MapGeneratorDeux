#pragma once

#include <cmath>

const float TILE_HEIGHT = 80.f;
const float TILE_WIDTH = 69.282032302755091741097853660235f;

// отношение сторон 30:19
const uint16_t MAP_WIDTH = 300;
const uint16_t MAP_HEIGHT = 190;

const uint16_t LAND_BORDER = 0.07f * MAP_HEIGHT;

// уровень моря, 0 - нет моря, 1 - море по средней высоте мира
const float OCEAN_LEVEL = 1.08f;

const uint16_t TEMPERATURE_MIN = 263;
const uint16_t TEMPERATURE_MAX = 323;

enum MapMode {
  NORMAL, TEMPERATURE, HEIGHT, BIOMES, MINIMAP, MOISTURE, SELECTED
};