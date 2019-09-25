#pragma once

#include <screens/Screen.h>

class MapScreen : public Screen {

private:
    void draw() override;

    void doAction() override;

public:
    explicit MapScreen(RenderWindow *renderWindow) : Screen(renderWindow) {};
};