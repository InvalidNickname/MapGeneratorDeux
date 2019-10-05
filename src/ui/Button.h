#pragma once

#include <functional>
#include <utility>

#include <SFML/Graphics.hpp>

#include "UIDrawable.h"

class Button : public UIDrawable {

  public:
    Button(float x, float y, float width, float height, Texture *normal, Texture *clicked,
           std::function<void()> onClick);

    void render(RenderWindow *window) override;

    bool checkClicked(float _x, float _y) override;

    void setClicked(bool _clicked);

    bool isClickable() override { return true; }

  private:
    Sprite sprite;
    float x, y, width, height;
    Texture *normal, *clicked;
    std::function<void()> onClick;

};
