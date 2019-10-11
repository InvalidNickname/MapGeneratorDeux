#pragma once

#include <functional>
#include <utility>

#include <SFML/Graphics.hpp>

#include "UIDrawable.h"

class Button : public UIDrawable {

 public:
  Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
         Texture *normal, Texture *clicked, std::function<void()> onClick);

  void render(RenderWindow *window) override;

  bool checkClicked(Vector2i coords) override;

  void setClicked(bool _clicked);

  bool isClickable() override { return true; }

 private:
  Sprite sprite;
  uint16_t x, y, width, height;
  Texture *normal, *clicked;
  const std::function<void()> onClick;

};
