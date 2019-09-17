#pragma once

#include "../Screen.h"

class SplashScreen : public Screen {

private:
    void draw() override;

public:
    explicit SplashScreen(RenderWindow *_window) : Screen(_window) {};
};