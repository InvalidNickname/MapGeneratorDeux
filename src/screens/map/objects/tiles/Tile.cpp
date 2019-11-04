#include "Tile.h"

Tile::Tile(uint16_t x, uint16_t y) : x(x), y(y) {
  setType("GenWater");
  tile_y = TILE_HEIGHT * ((float) y - (float) (y / 2) / 2 - (y % 2 == 1 ? 0.25f : 0));
  shape = VertexArray(TriangleFan, 8);
  latitude = 90 * (1 - (2.f * y / MAP_HEIGHT > 1 ? 2 - 2.f * y / MAP_HEIGHT : 2.f * y / MAP_HEIGHT));
  longitude = 180 * (1 - (2.f * x / MAP_WIDTH > 1 ? 2 - 2.f * x / MAP_WIDTH : 2.f * x / MAP_WIDTH));
}

void Tile::render(RenderTarget *_target, MapMode mode, int16_t _x, int16_t _y, int max_z, int min_z) {
  float temp;
  Color color;
  switch (mode) {
    case NORMAL:color = type->getBaseColor(level);
      break;
    case TEMPERATURE:temp = (float) (temperature - TEMPERATURE_MIN) / (float) (TEMPERATURE_MAX - TEMPERATURE_MIN);
      color = Color(255, (1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case HEIGHT:temp = (float) (z - min_z) / (float) (max_z - min_z + 1);
      color = Color((1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case BIOMES:color = type->getBiomeColor();
      break;
    case MINIMAP:
      if (type->getArchtype() == "Water") {
        color = Color(179, 171, 128);
      } else {
        color = Color(108, 106, 68);
      }
      break;
    case MOISTURE:color = Color((1 - moisture) * 255, (1 - moisture) * 255, 255, 255);
      break;
    case SELECTED:color = Color(0, 0, 0, 150);
      break;
  }
  // координаты для отрисовки
  tile_x = TILE_WIDTH * ((float) _x + (_y % 2 == 1 ? 0.5f : 0));
  drawTile(_target, color);
}

void Tile::drawTile(RenderTarget *_target, Color color) {
  shape[0].position = Vector2f(tile_x + TILE_WIDTH / 2, tile_y + TILE_HEIGHT / 2);
  shape[0].color = color;
  shape[1].position = Vector2f(tile_x + TILE_WIDTH / 2, tile_y + TILE_HEIGHT);
  shape[1].color = color;
  shape[2].position = Vector2f(tile_x + TILE_WIDTH, tile_y + TILE_HEIGHT * 3 / 4.f);
  shape[2].color = color;
  shape[3].position = Vector2f(tile_x + TILE_WIDTH, tile_y + TILE_HEIGHT / 4.f);
  shape[3].color = color;
  shape[4].position = Vector2f(tile_x + TILE_WIDTH / 2, tile_y);
  shape[4].color = color;
  shape[5].position = Vector2f(tile_x, tile_y + TILE_HEIGHT / 4.f);
  shape[5].color = color;
  shape[6].position = Vector2f(tile_x, tile_y + TILE_HEIGHT * 3 / 4.f);
  shape[6].color = color;
  shape[7].position = Vector2f(tile_x + TILE_WIDTH / 2, tile_y + TILE_HEIGHT);
  shape[7].color = color;
  _target->draw(shape);
}

float Tile::getLatitude() const {
  return latitude;
}

float Tile::getLongitude() const {
  return longitude;
}

uint16_t Tile::getX() const {
  return x;
}

uint16_t Tile::getY() const {
  return y;
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

Level Tile::GetLevel() const {
  return level;
}
