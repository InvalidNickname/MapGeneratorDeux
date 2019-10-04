#pragma once

#include <functional>
#include <utility>

#include <SFML/Graphics.hpp>

using namespace sf;

class Button {

  public:
    Button(int x, int y, int width, int height, Texture *normal, Texture *clicked, std::function<void()> onClick);

    void render(RenderWindow *window);

    bool checkClicked(int _x, int _y);

  private:
    Sprite sprite;
    int x, y, width, height;
    Texture *normal, *clicked;
    std::function<void()> onClick;

};
