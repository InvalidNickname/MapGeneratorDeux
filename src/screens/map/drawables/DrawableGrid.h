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

  void renderVector(RenderTarget *_target, MapMode mode, Vector2s lower_left, Vector2s upper_right);

  Vector2s updateSelection(Vector2f position);

  Vector2s static getTileByCoordinates(Vector2f coords);

  Tile *getTile(Vector2s coords);

 private:
  TileGrid *tile_grid;
  Vector2s selected{-1, -1};
  int max_z, min_z;
  RenderTexture *center;
  Sprite s_left, s_center, s_right;
  Sprite selected_tile;
  MapMode prev_mode{};

  void updateTexture(MapMode mode);

  void renderSelectedTile(RenderTarget *_target, int x0, int x1);

};