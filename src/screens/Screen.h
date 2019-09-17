#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Screen {

private:
    RenderWindow *window;

public:
    virtual void draw() = 0;

    explicit Screen(RenderWindow *_window) : window(_window) {}

};