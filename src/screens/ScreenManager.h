#pragma once

#include "Screen.h"

class ScreenManager {

private:
    Screen *activeScreen;

public:
    void drawActiveScreen();

    void setActiveScreen(Screen *screen);

};