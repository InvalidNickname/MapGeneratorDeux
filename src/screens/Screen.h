#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <utility>

using namespace sf;

class Screen {

  public:
    virtual void draw() = 0;

    virtual void doAction() = 0;

    explicit Screen(RenderWindow *_window) : window(_window) {}

    void setMoveFunction(std::function<void(Screen *)> _move) {
        move = std::move(_move);
    }

  protected:
    RenderWindow *window;
    std::function<void(Screen *)> move;

};