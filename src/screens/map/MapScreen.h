#pragma once

#include "../Screen.h"

class MapScreen : public Screen {

private:
    void draw() override;

public:
    explicit MapScreen(RenderWindow *renderWindow) : Screen(renderWindow) {};
};