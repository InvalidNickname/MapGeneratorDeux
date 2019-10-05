#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class UIDrawable {
  public:
    virtual void render(RenderWindow *window) = 0;

    virtual bool checkClicked(float _x, float _y) = 0;

    virtual bool isClickable() = 0;

};
