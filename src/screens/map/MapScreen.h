#pragma once

#include <screens/Screen.h>
#include <screens/map/objects/DrawableGrid.h>
#include "MapParameters.h"

#define isKeyPressed Keyboard::isKeyPressed

class MapScreen : public Screen {

  public:
    float minZoom;

  private:
    float windowHeight, windowWidth;

    View view;
    MapMode mapMode{MapMode::NORMAL};
    float zoom;
    float initialWidth, initialHeight;
    DrawableGrid *drawableGrid;

    void draw() override;

    void doAction() override;

    void handleInput();

  public:
    explicit MapScreen(RenderWindow *renderWindow);
};