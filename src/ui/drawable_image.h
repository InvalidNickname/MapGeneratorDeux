#ifndef MGD_SRC_UI_DRAWABLE_IMAGE_H
#define MGD_SRC_UI_DRAWABLE_IMAGE_H

#include "ui_drawable.h"

class DrawableImage : public UIDrawable {
 public:
  DrawableImage(Vector2s position, Vector2s size, Texture *texture);

  void Render(RenderWindow *window) override;

  [[nodiscard]] bool CheckClicked(Vector2i coords) override { return false; };

  [[nodiscard]] bool IsClickable() override { return false; };

 private:
  Sprite sprite_;
};

#endif