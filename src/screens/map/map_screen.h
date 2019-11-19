#ifndef MGD_SRC_SCREENS_MAP_MAP_SCREEN_H
#define MGD_SRC_SCREENS_MAP_MAP_SCREEN_H

#include "screens/screen.h"
#include "ui/gui.h"
#include "screens/map/drawables/minimap.h"
#include "ui/radio_buttons.h"
#include "screens/map/drawables/tile_info_list.h"

class MapScreen : public Screen {

  using Screen::Screen;

 public:
  float min_zoom_;

 private:
  Vector2u window_size_, initial_size_;
  View map_, ui_;
  MapMode map_mode_{NORMAL};
  float zoom_;
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