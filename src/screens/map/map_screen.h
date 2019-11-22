#ifndef MGD_SRC_SCREENS_MAP_MAP_SCREEN_H
#define MGD_SRC_SCREENS_MAP_MAP_SCREEN_H

#include <gui.h>
#include <radio_buttons.h>
#include <drawable_text.h>

#include "screens/screen.h"
#include "screens/map/drawables/minimap.h"

class MapScreen : public Screen {

  using Screen::Screen;

 private:
  Vector2u window_size_, initial_size_;
  View map_, ui_;
  MapMode map_mode_{NORMAL};
  float zoom_, min_zoom_;
  DrawableGrid *grid_;
  GUI *gui_;

  void Draw() override;

  GameState DoAction() override;

  void Prepare() override;

  void SetGUI();

  void HandleInput();

  void ZoomAtPoint(Vector2i point);
};

#endif