#include "Tile.h"

Tile::Tile(Vector2u pos) : pos(pos) {
  setType("GenWater");
  latitude = 90 * (1 - (2.f * pos.y / G::GetMapH() > 1 ? 2 - 2.f * pos.y / G::GetMapH() : 2.f * pos.y / G::GetMapH()));
  longitude =
      180 * (1 - (2.f * pos.x / G::GetMapW() > 1 ? 2 - 2.f * pos.x / G::GetMapW() : 2.f * pos.x / G::GetMapW()));
}

float Tile::getLatitude() const {
  return latitude;
}

float Tile::getLongitude() const {
  return longitude;
}

uint16_t Tile::getZ() const {
  return z;
}

Type *Tile::getType() const {
  return type;
}

void Tile::setLevel(Level _level) {
  level = _level;
}

void Tile::setType(const string &_type) {
  type = Tileset::get().getType(_type);
}

void Tile::increaseZ(int _z) {
  z += _z;
}

uint16_t Tile::getTemperature() const {
  return temperature;
}

void Tile::setTemperature(uint16_t _temperature) {
  temperature = _temperature;
}

float Tile::getMoisture() const {
  return moisture;
}

void Tile::setMoisture(float _moisture) {
  moisture = _moisture;
}

void Tile::setZ(uint16_t _z) {
  z = _z;
}

Level Tile::getLevel() const {
  return level;
}
