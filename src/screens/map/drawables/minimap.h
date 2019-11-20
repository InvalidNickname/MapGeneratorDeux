#ifndef MGD_SRC_SCREENS_MAP_DRAWABLES_MINIMAP_H
#define MGD_SRC_SCREENS_MAP_DRAWABLES_MINIMAP_H

#include <ui_drawable.h>

#include "utils/r.h"
#include "drawable_grid.h"

using namespace sf;

class Minimap : public UIDrawable {
 public:
  Minimap(Vector2u window_size, DrawableGrid *drawable_grid);

  void Render(RenderWindow *window) override;

  bool IsClickable() override { return false; };

  bool CheckClicked(Vector2i coords) override { return false; };

  void UpdateViewRegion(Vector2s lower_left, Vector2s upper_right);

 private:
  Sprite minimap_, overlay_;
  RectangleShape left_, right_;
  Vector2u window_size_;
  Vector2f pos_;

  void CreateMinimapImage(DrawableGrid *drawable_grid);

  void CreateViewRectangles();
};

#endif