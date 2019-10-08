#include "Tile.h"

Tile::Tile(uint16_t x, uint16_t y) : x(x), y(y) {
    setType("GenWater");
    tileY = TILE_HEIGHT * ((float) y - (float) (y / 2) / 2 - (y % 2 == 1 ? 0.25f : 0));
    shape = VertexArray(TriangleFan, 8);
    latitude = 90 * (1 - (2.f * y / MAP_HEIGHT > 1 ? 2 - 2.f * y / MAP_HEIGHT : 2.f * y / MAP_HEIGHT));
    longitude = 180 * (1 - (2.f * x / MAP_WIDTH > 1 ? 2 - 2.f * x / MAP_WIDTH : 2.f * x / MAP_WIDTH));
}

void Tile::render(RenderTarget *_target, MapMode mode, int16_t _x, int16_t _y, int maxZ, int minZ) {
    float temp;
    Color color;
    switch (mode) {
        case NORMAL:
            color = type->getBaseColor(level);
            break;
        case TEMPERATURE:
            temp = (float) (temperature + abs(TEMPERATURE_MIN) + 1) /
                   (float) (abs(TEMPERATURE_MIN) + abs(TEMPERATURE_MAX) + 2);
            color = Color(255, (1 - temp) * 255, (1 - temp) * 255, 255);
            break;
        case HEIGHT:
            temp = (float) (z - minZ) / (float) (maxZ - minZ + 1);
            color = Color((1 - temp) * 255, (1 - temp) * 255, 255);
            break;
        case BIOMES:
            color = type->getBiomeColor();
            break;
        case MINIMAP:
            if (type->getArchtype() == "Water") {
                return;
            } else {
                color = Color(108, 106, 68);
            }
            break;
        case MOISTURE:
            color = Color((1 - moisture) * 255, (1 - moisture) * 255, 255, 255);
            break;
        case SELECTED:
            color = Color(0, 0, 0, 150);
            break;
    }
    // координаты для отрисовки
    tileX = TILE_WIDTH * ((float) _x + (_y % 2 == 1 ? 0.5f : 0));
    drawTile(_target, color);
}

void Tile::drawTile(RenderTarget *_target, Color color) {
    shape[0].position = Vector2f(tileX + TILE_WIDTH / 2, tileY + TILE_HEIGHT / 2);
    shape[0].color = color;
    shape[1].position = Vector2f(tileX + TILE_WIDTH / 2, tileY + TILE_HEIGHT);
    shape[1].color = color;
    shape[2].position = Vector2f(tileX + TILE_WIDTH, tileY + TILE_HEIGHT * 3 / 4.f);
    shape[2].color = color;
    shape[3].position = Vector2f(tileX + TILE_WIDTH, tileY + TILE_HEIGHT / 4.f);
    shape[3].color = color;
    shape[4].position = Vector2f(tileX + TILE_WIDTH / 2, tileY);
    shape[4].color = color;
    shape[5].position = Vector2f(tileX, tileY + TILE_HEIGHT / 4.f);
    shape[5].color = color;
    shape[6].position = Vector2f(tileX, tileY + TILE_HEIGHT * 3 / 4.f);
    shape[6].color = color;
    shape[7].position = Vector2f(tileX + TILE_WIDTH / 2, tileY + TILE_HEIGHT);
    shape[7].color = color;
    _target->draw(shape);
}

float Tile::getLatitude() {
    return latitude;
}

float Tile::getLongitude() {
    return longitude;
}

uint16_t Tile::getX() {
    return x;
}

uint16_t Tile::getY() {
    return y;
}

int Tile::getZ() {
    return z;
}

Type *Tile::getType() {
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

int16_t Tile::getTemperature() {
    return temperature;
}

void Tile::setTemperature(int16_t _temperature) {
    temperature = _temperature;
}

float Tile::getMoisture() {
    return moisture;
}

void Tile::setMoisture(float _moisture) {
    moisture = _moisture;
}