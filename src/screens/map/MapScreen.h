#pragma once

#include <screens/Screen.h>
#include <screens/map/drawables/DrawableGrid.h>
#include <screens/map/generator/GenerationParameters.h>
#include <screens/map/drawables/GUI.h>

class MapScreen : public Screen {

    using Screen::Screen;

  public:
    float minZoom;

  private:
    float windowHeight, windowWidth;
    View mapView, uiView;
    MapMode mapMode{MapMode::NORMAL};
    float zoom;
    float initialWidth, initialHeight;
    DrawableGrid *drawableGrid;
    GUI *gui;

    void draw() override;

    int doAction() override;

    void prepare() override;

    void handleInput();

    void zoomAtPoint(Vector2i point);
};