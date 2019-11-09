#pragma once

#include "ui/UIDrawable.h"
#include "utils/GenerationParameters.h"
#include "utils/R.h"
#include "DrawableGrid.h"

using namespace sf;

class Minimap : public UIDrawable {
 public:
  Minimap(Vector2u window_size, DrawableGrid *drawable_grid);

  void render(RenderWindow *window) override;

  bool isClickable() override { return false; };

  bool checkClicked(Vector2i coords) override { return false; };

  void updateViewRegion(Vector2s lower_left, Vector2s upper_right);

 private:
  Sprite minimap, overlay;
  RectangleShape left, right;
  Vector2u window_size;
  Vector2f pos;

  void createMinimapImage(DrawableGrid *drawable_grid);

  void createViewRectangles();

};
