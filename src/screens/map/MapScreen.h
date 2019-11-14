#pragma once

#include "screens/Screen.h"
#include "ui/GUI.h"
#include "screens/map/drawables/Minimap.h"
#include "ui/RadioButtons.h"
#include "screens/map/drawables/TileInfoList.h"

class MapScreen : public Screen {

  using Screen::Screen;

 public:
  float min_zoom;

 private:
  Vector2u window_size, initial_size;
  View map_view, ui_view;
  MapMode map_mode{NORMAL};
  float zoom;
  DrawableGrid *drawable_grid;
  GUI *gui;

  void draw() override;

  GameState doAction() override;

  void prepare() override;

  void setGUI();

  void handleInput();

  void zoomAtPoint(Vector2i point);
};