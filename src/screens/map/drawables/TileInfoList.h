#pragma once

#include <codecvt>

#include <tile/Tile.h>

#include "ui/UIDrawable.h"
#include "utils/AssetLoader.h"

class TileInfoList : public UIDrawable {
 public:
  explicit TileInfoList(Vector2u window_size);

  void setTile(Tile *tile);

  void render(RenderWindow *window) override;

  bool isClickable() override { return false; };

  bool checkClicked(Vector2i coords) override { return false; };

 private:
  Text coordinates, type, temperature;
  Sprite background;

  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
};
