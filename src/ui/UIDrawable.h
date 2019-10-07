#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class UIDrawable {
  public:
    virtual void render(RenderWindow *window) = 0;

    virtual bool checkClicked(Vector2i coords) = 0;

    virtual bool isClickable() = 0;

};
