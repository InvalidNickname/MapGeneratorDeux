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
  float min_zoom;

 private:
  uint16_t window_height, window_width;
  View map_view, ui_view;
  MapMode map_mode{MapMode::NORMAL};
  float zoom;
  uint16_t initial_width, initial_height;
  DrawableGrid *drawable_grid;
  GUI *gui;

  void draw() override;

  int doAction() override;

  void prepare() override;

  void setGUI();

  void handleInput();

  void zoomAtPoint(Vector2i point);
};