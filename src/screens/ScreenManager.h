#pragma once

#include "Screen.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class ScreenManager {

  public:
    void drawActiveScreen();

    void doActiveScreenActions();

    explicit ScreenManager(Screen *_screen);

    void setActiveScreen(Screen *_screen);

  private:
    Screen *activeScreen{};

};