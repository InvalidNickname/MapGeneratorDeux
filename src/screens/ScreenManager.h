#pragma once

#include "Screen.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class ScreenManager {

private:
    Screen *activeScreen;

public:
    void drawActiveScreen();

    explicit ScreenManager(Screen *activeScreen);

    void setActiveScreen(Screen *screen);

};