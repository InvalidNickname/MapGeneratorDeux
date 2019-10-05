#pragma once

#include <screens/Screen.h>
#include <screens/map/drawables/DrawableGrid.h>
#include <utils/GenerationParameters.h>
#include <screens/map/drawables/GUI.h>
#include <screens/map/drawables/Minimap.h>
#include <ui/RadioButtons.h>

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

    void setGUI();

    void handleInput();

    void zoomAtPoint(Vector2i point);
};