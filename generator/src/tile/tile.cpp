#include "tile.h"

Tile::Tile(Vector2u pos) : pos_(pos) {
  SetType("GenWater");
  latitude_ = 90 * (1 - (2.f * pos.y / G::GetMapH() > 1 ? 2 - 2.f * pos.y / G::GetMapH() : 2.f * pos.y / G::GetMapH()));
  longitude_ =
      180 * (1 - (2.f * pos.x / G::GetMapW() > 1 ? 2 - 2.f * pos.x / G::GetMapW() : 2.f * pos.x / G::GetMapW()));
}

float Tile::GetLatitude() const {
  return latitude_;
}

float Tile::GetLongitude() const {
  return longitude_;
}

uint16_t Tile::GetZ() const {
  return z_;
}

Type *Tile::GetType() const {
  return type_;
}

void Tile::SetLevel(Level level) {
  level_ = level;
}

void Tile::SetType(const string &type) {
  type_ = Tileset::Get().GetType(type);
}

void Tile::IncreaseZ(int z) {
  z_ += z;
}

uint16_t Tile::GetTemperature() const {
  return temperature_;
}

void Tile::SetTemperature(uint16_t temperature) {
  temperature_ = temperature;
}

float Tile::GetMoisture() const {
  return moisture_;
}

void Tile::SetMoisture(float moisture) {
  moisture_ = moisture;
}

void Tile::SetZ(uint16_t z) {
  z_ = z;
}

Level Tile::GetLevel() const {
  return level_;
}
