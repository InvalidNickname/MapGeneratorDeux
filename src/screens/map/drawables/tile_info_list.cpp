#include "tile_info_list.h"

TileInfoList::TileInfoList(Vector2u window_size) {
  coordinates_ = Text("", *AssetLoader::Get().GetFont("default"), 20);
  coordinates_.setPosition(20, (float) window_size.y - 60);
  type_ = Text("", *AssetLoader::Get().GetFont("default"));
  type_.setPosition(20, (float) window_size.y - 95);
  temperature_ = Text("", *AssetLoader::Get().GetFont("default"), 20);
  temperature_.setPosition(20, (float) window_size.y - 40);
}

void TileInfoList::SetTile(Tile *tile) {
  auto latitudeText
      (to_string((int) tile->GetLatitude()) + (tile->pos_.y < G::GetMapH() / 2 ? " \u00B0N" : " \u00B0S")); // °N, °S
  auto longitudeText
      (to_string((int) tile->GetLongitude()) + (tile->pos_.x > G::GetMapW() / 2 ? " \u00B0E" : " \u00B0W")); // °E, °W
  coordinates_.setString(latitudeText + " " + longitudeText);
  type_.setString(converter_.from_bytes(tile->GetType()->GetName(tile->GetLevel())));
  temperature_.setString(String(to_string(tile->GetTemperature() - 273) + " \u00B0C")); // °C
}

void TileInfoList::Render(RenderWindow *window) {
  window->draw(background_);
  window->draw(coordinates_);
  window->draw(type_);
  window->draw(temperature_);
}