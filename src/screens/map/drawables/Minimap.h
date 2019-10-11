#pragma once

#include <ui/UIDrawable.h>

#include <utils/AssetLoader.h>
#include <utils/GenerationParameters.h>

#include "DrawableGrid.h"

using namespace sf;

class Minimap : public UIDrawable {
 public:
  Minimap(uint16_t window_width, uint16_t window_height, DrawableGrid *drawable_grid);

  void render(RenderWindow *window) override;

  bool isClickable() override { return false; };

  bool checkClicked(Vector2i coords) override { return false; };

  void updateViewRegion(Vector2s lower_left, Vector2s upper_right);

 private:
  RenderTexture *minimap_texture = nullptr;
  Sprite minimap;
  RectangleShape left, right, center;
  uint16_t window_width, window_height;

  float MINIMAP_X, MINIMAP_Y;
  const float MINIMAP_W{300}, MINIMAP_H{190};

  void createMinimapImage(DrawableGrid *drawable_grid);

  void createViewRectangles();

};
