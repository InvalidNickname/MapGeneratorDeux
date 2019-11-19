#pragma once

#include "UIDrawable.h"

class DrawableImage : public UIDrawable {
 public:
  DrawableImage(Vector2s position, Vector2s size, Texture *texture);

  void Render(RenderWindow *window) override;

  [[nodiscard]] bool CheckClicked(Vector2i coords) override { return false; };

  [[nodiscard]] bool IsClickable() override { return false; };

 private:
  Sprite sprite_;
};
