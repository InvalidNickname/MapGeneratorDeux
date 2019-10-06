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
    Tile(int x, int y);

    void render(RenderTarget *_target, MapMode mode, int _x, int _y, int maxZ, int minZ);

    float getLatitude();

    float getLongitude();

    int getX();

    int getY();

    int getZ();

    Type *getType();

    void setLevel(Level _level);

    void setType(const string &type);

    void increaseZ(int z);

    float getTemperature();

    void setTemperature(int temperature);

    float getMoisture();

    void setMoisture(float _moisture);

  private:
    int x, y, z{0};
    float latitude, longitude;
    float tileX{0}, tileY{0};
    float temperature{0}, moisture{0};
    Type *type{nullptr};
    Level level{Level::NO};
    VertexArray shape;

    void drawTile(RenderTarget *_target, Color color);
};