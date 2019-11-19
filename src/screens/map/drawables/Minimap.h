#pragma once

#include "ui/UIDrawable.h"
#include "utils/R.h"
#include "DrawableGrid.h"

using namespace sf;

class Minimap : public UIDrawable {
 public:
  Minimap(Vector2u window_size, DrawableGrid *drawable_grid);

  void Render(RenderWindow *window) override;

  bool IsClickable() override { return false; };

  bool CheckClicked(Vector2i coords) override { return false; };

  void updateViewRegion(Vector2s lower_left, Vector2s upper_right);

 private:
  Sprite minimap, overlay;
  RectangleShape left, right;
  Vector2u window_size;
  Vector2f pos;

  void createMinimapImage(DrawableGrid *drawable_grid);

  void createViewRectangles();

};
