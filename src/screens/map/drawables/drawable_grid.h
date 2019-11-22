#ifndef MGD_SRC_SCREENS_MAP_DRAWABLES_DRAWABLE_GRID_H
#define MGD_SRC_SCREENS_MAP_DRAWABLES_DRAWABLE_GRID_H

#include <generator.h>

#include "utils/asset_loader.h"
#include "utils/r.h"
#include "screens/map/map_mode.h"

using Vector2s = Vector2<int16_t>;

class DrawableGrid {
 public:
  DrawableGrid();

  void RenderGridTexture(RenderTarget *target, MapMode mode, int x0, int x1);

  void RenderVector(RenderTarget *target, MapMode mode, Vector2s lower_left, Vector2s upper_right);

  Vector2u UpdateSelection(Vector2f position);

  [[nodiscard]] Vector2s static GetTileByCoords(Vector2f coords);

  [[nodiscard]] Tile *GetTile(Vector2u coords) const;

  [[nodiscard]] Vector2<uint16_t> GetSize() const;

 private:
  TileGrid *grid_;
  Vector2s selected_{-1, -1};
  int max_z_, min_z_;
  RenderTexture *center_;
  Sprite s_left_, s_center_, s_right_;
  Sprite selected_tile_;
  MapMode prev_mode_{};
  VertexArray river;

  void UpdateTexture(MapMode mode);

  void RenderSelectedTile(RenderTarget *target, int x0, int x1);

  void RenderTile(RenderTarget *target, MapMode mode, Vector2u coords, Vector2i pos);

  static void RenderTileTriangles(RenderTarget *target, Color color, Vector2i pos);

  void RenderRiver(RenderTarget *target, Vector2u coords, Vector2i pos);

  static uint16_t GetRotation(uint8_t direction);
};

#endif