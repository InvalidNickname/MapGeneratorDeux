#pragma once

#include <screens/Screen.h>
#include <screens/map/drawables/DrawableGrid.h>
#include <utils/GenerationParameters.h>
#include <ui/GUI.h>
#include <screens/map/drawables/Minimap.h>
#include <ui/RadioButtons.h>

class MapScreen : public Screen {

    using Screen::Screen;

  public:
    float minZoom;

  private:
    uint16_t windowHeight, windowWidth;
    View mapView, uiView;
    MapMode mapMode{MapMode::NORMAL};
    float zoom;
    uint16_t initialWidth, initialHeight;
    DrawableGrid *drawableGrid;
    GUI *gui;

    void draw() override;

    int doAction() override;

    void prepare() override;

    void setGUI();

    void handleInput();

    void zoomAtPoint(Vector2i point);
};