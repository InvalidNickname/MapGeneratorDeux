#pragma once

#include "../Screen.h"

class MapScreen : public Screen {

private:
    RenderWindow *window;

    void draw() override;

public:
    explicit MapScreen(RenderWindow *_window);
};