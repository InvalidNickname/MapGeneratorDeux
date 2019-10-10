#pragma once

#include <screens/map/objects/tiles/TileGrid.h>
#include <utils/GenerationParameters.h>
#include <utils/AssetLoader.h>
#include <screens/map/generator/Generator.h>

using Vector2s = Vector2<int16_t>;

class DrawableGrid {
  public:
    DrawableGrid();

    void renderTexture(RenderTarget *_target, MapMode mode, int x0, int x1);

    void renderVector(RenderTarget *_target, MapMode mode, Vector2s lowerLeft, Vector2s upperRight);

    void updateSelection(Vector2f position);

    Vector2s static getTileByCoordinates(Vector2f coords);

  private:
    TileGrid *tileGrid;
    Vector2s selected{-1, -1};
    int maxZ, minZ;
    RenderTexture *center;
    Sprite sLeft, sCenter, sRight;
    Sprite selectedTile;
    MapMode prev{};

    void updateTexture(MapMode mode);

    void renderSelectedTile(RenderTarget *_target, int x0, int x1);

};