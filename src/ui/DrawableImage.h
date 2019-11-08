#pragma once

#include "UIDrawable.h"

class DrawableImage : public UIDrawable {
 public:
  DrawableImage(Vector2s position, Vector2s size, Texture *texture);

  void render(RenderWindow *window) override;

  [[nodiscard]] bool checkClicked(Vector2i coords) override { return false; };

  [[nodiscard]] bool isClickable() override { return false; };

 private:
  Sprite sprite_;
};
