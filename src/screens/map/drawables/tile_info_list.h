#ifndef MGD_SRC_SCREENS_MAP_DRAWABLES_TILE_INFO_LIST
#define MGD_SRC_SCREENS_MAP_DRAWABLES_TILE_INFO_LIST

#include <codecvt>

#include <tile/tile.h>

#include "ui/ui_drawable.h"
#include "utils/asset_loader.h"

//TODO убрать класс, занести все в MapScreen как объекты в GUI
class TileInfoList : public UIDrawable {
 public:
  explicit TileInfoList(Vector2u window_size);

  void SetTile(Tile *tile);

  void Render(RenderWindow *window) override;

  bool IsClickable() override { return false; };

  bool CheckClicked(Vector2i coords) override { return false; };

 private:
  Text coordinates_, type_, temperature_;
  Sprite background_;

  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter_;
};

#endif