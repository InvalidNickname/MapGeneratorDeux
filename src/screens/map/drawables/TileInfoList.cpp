#include "TileInfoList.h"

TileInfoList::TileInfoList(uint16_t window_width, uint16_t window_height) {
  coordinates = Text("", *AssetLoader::get().getFont("default"), 20);
  coordinates.setPosition(20, (float) window_height - 60);
  type = Text("No tiles selected", *AssetLoader::get().getFont("default"));
  type.setPosition(20, (float) window_height - 95);
  temperature = Text("", *AssetLoader::get().getFont("default"), 20);
  temperature.setPosition(20, (float) window_height - 40);
}

void TileInfoList::setTile(Tile *tile) {
  String latitudeText
      (to_string((int) tile->getLatitude()) + (tile->getY() < MAP_HEIGHT / 2 ? L" \u00B0N" : L" \u00B0S")); // °N, °S
  String longitudeText
      (to_string((int) tile->getLongitude()) + (tile->getX() > MAP_WIDTH / 2 ? L" \u00B0E" : L" \u00B0W")); // °E, °W
  coordinates.setString(latitudeText + " " + longitudeText);
  type.setString(tile->getType()->getName(tile->GetLevel()));
  temperature.setString(String(to_string(tile->getTemperature() - 273) + L" \u00B0C")); // °C
}

void TileInfoList::render(RenderWindow *window) {
  window->draw(background);
  window->draw(coordinates);
  window->draw(type);
  window->draw(temperature);
}