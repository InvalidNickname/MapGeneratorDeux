#pragma once

#include <screens/Screen.h>
#include "screens/map/drawables/DrawableGrid.h"
#include "screens/map/generator/GenerationParameters.h"

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

    inline static bool isKeyPressed(Keyboard::Key key);

  public:
    explicit MapScreen(RenderWindow *renderWindow);
};