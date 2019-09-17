#pragma once

#include "../Screen.h"

class SplashScreen : public Screen {

private:
    RenderWindow *window;

    void draw() override;

public:
    explicit SplashScreen(RenderWindow *_window);
};