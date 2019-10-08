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

    void render(RenderTarget *_target, MapMode mode, int16_t _x, int16_t _y, int maxZ, int minZ);

    float getLatitude();

    float getLongitude();

    uint16_t getX();

    uint16_t getY();

    int getZ();

    Type *getType();

    void setLevel(Level _level);

    void setType(const string &type);

    void increaseZ(int z);

    int16_t getTemperature();

    void setTemperature(int16_t temperature);

    float getMoisture();

    void setMoisture(float _moisture);

  private:
    uint16_t x, y;
    int z{0};
    float latitude, longitude;
    float tileX{0}, tileY{0};
    float moisture{0};
    int16_t temperature{0};
    Type *type{nullptr};
    Level level{Level::NO};
    VertexArray shape;

    void drawTile(RenderTarget *_target, Color color);
};