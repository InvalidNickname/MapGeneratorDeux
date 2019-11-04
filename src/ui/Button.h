#pragma once

#include <functional>
#include <utility>

#include <SFML/Graphics.hpp>

#include "UIDrawable.h"

using namespace std;

class Button : public UIDrawable {

 public:
  Button(Vector2s position, Vector2s size, Texture *normal, Texture *clicked, function<void()> onClick);

  void render(RenderWindow *window) override;

  bool checkClicked(Vector2i coords) override;

  void setClicked(bool _clicked);

  bool isClickable() override { return true; }

 private:
  Sprite sprite;
  Texture *normal, *clicked;
  const function<void()> onClick;

};
