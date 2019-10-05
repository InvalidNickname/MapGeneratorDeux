#pragma once

#include <cmath>

const float TILE_HEIGHT = 80.f;
const float TILE_WIDTH = 69.282032302755091741097853660235f;

const int MAP_WIDTH = 300;
const int MAP_HEIGHT = 190;

const int LAND_BORDER = (int) (0.07 * MAP_HEIGHT);

// уровень моря, 0 - нет моря, 1 - море по средней высоте мира
const float OCEAN_LEVEL = 1.08f;

const int TEMPERATURE_MIN = -10;
const int TEMPERATURE_MAX = 50;

enum MapMode {
    NORMAL, TEMPERATURE, HEIGHT, BIOMES, MINIMAP
};