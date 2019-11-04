#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

using Vector2s = Vector2<int16_t>;

class UIDrawable {
 public:
  virtual void render(RenderWindow *window) = 0;

  [[nodiscard]] virtual bool checkClicked(Vector2i coords) = 0;

  [[nodiscard]] virtual bool isClickable() = 0;

};
