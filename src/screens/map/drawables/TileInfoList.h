#pragma once

#include "ui/UIDrawable.h"
#include "screens/map/objects/tiles/Tile.h"
#include "utils/AssetLoader.h"

class TileInfoList : public UIDrawable {
 public:
  TileInfoList(uint16_t window_width, uint16_t window_height);

  void setTile(Tile *tile);

  void render(RenderWindow *window) override;

  bool isClickable() override { return false; };

  bool checkClicked(Vector2i coords) override { return false; };

 private:
  Text coordinates, type, temperature;
  Sprite background;
};
