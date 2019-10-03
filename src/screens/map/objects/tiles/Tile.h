#pragma once

#include "type/Type.h"
#include <screens/map/generator/GenerationParameters.h>
#include <SFML/Graphics.hpp>
#include "type/Tileset.h"
#include <cmath>

using namespace sf;

class Tile {
  private:
    int x, y;
    int z{0};
    float latitude, longitude;
    float tileX{0}, tileY{0};
    float temperature;
    Type *type;
    Level level{Level::NO};
    VertexArray shape;
  public:
    Tile(int x, int y);

    void render(RenderWindow *_window, MapMode mode, int _x, int _y, int maxZ, int minZ);

    float getLatitude();

    float getLongitude();

    int getX();

    int getY();

    int getZ();

    Type *getType();

    void setLevel(Level _level);

    void setType(const string &type);

    void increaseZ(int z);

  private:
    void drawTile(RenderWindow *_window, Color color);
};