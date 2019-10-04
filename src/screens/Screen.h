#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"

using namespace sf;

class Screen {

  public:
    explicit Screen(RenderWindow *_window) : window(_window) {}

    virtual void prepare() = 0;

    virtual int doAction() = 0;

    virtual void draw() = 0;

  protected:
    RenderWindow *window;

};