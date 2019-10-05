#pragma once

#include <screens/map/objects/tiles/TileGrid.h>
#include <screens/map/generator/GenerationParameters.h>
#include <screens/map/generator/Generator.h>

class DrawableGrid {
  public:
    DrawableGrid();

    void render(RenderTarget *_target, MapMode mode, int x0, int x1);

    void render(RenderTarget *_target, MapMode mode, int x0, int y0, int x1, int y1);

    Vector2i static getTileByCoordinates(Vector2f coords);

  private:
    TileGrid *tileGrid;
    int selectedX{-1}, selectedY{-1};
    int maxZ, minZ;
    RenderTexture *center;
    Sprite sLeft, sCenter, sRight;
    MapMode prev{};

    void updateTexture(MapMode mode);

};