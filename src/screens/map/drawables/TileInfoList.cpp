#include "TileInfoList.h"

TileInfoList::TileInfoList(Vector2u window_size) {
  coordinates = Text("", *AssetLoader::get().getFont("default"), 20);
  coordinates.setPosition(20, (float) window_size.y - 60);
  type = Text("No tiles selected", *AssetLoader::get().getFont("default"));
  type.setPosition(20, (float) window_size.y - 95);
  temperature = Text("", *AssetLoader::get().getFont("default"), 20);
  temperature.setPosition(20, (float) window_size.y - 40);
}

void TileInfoList::setTile(Tile *tile) {
  auto latitudeText
      (to_string((int) tile->getLatitude()) + (tile->pos.y < G::GetMapH() / 2 ? " \u00B0N" : " \u00B0S")); // °N, °S
  auto longitudeText
      (to_string((int) tile->getLongitude()) + (tile->pos.x > G::GetMapW() / 2 ? " \u00B0E" : " \u00B0W")); // °E, °W
  coordinates.setString(latitudeText + " " + longitudeText);
  type.setString(tile->getType()->getName(tile->getLevel()));
  temperature.setString(String(to_string(tile->getTemperature() - 273) + " \u00B0C")); // °C
}

void TileInfoList::render(RenderWindow *window) {
  window->draw(background);
  window->draw(coordinates);
  window->draw(type);
  window->draw(temperature);
}