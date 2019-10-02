#include <screens/map/objects/tiles/type/Tileset.h>
#include "Tile.h"

Tile::Tile(int x, int y) : x(x), y(y) {
    tileY = TILE_HEIGHT * ((float) y - (float) (y / 2) / 2 - (y % 2 == 1 ? 0.25f : 0));
    tileShape.setPointCount(6);
}

void Tile::render(RenderWindow *_window, MapMode mode, int _x, int _y, int maxZ, int minZ) {
    float temp;
    switch (mode) {
        case NORMAL:
            tileShape.setFillColor(type->getBaseColor(level));
            break;
        case TEMPERATURE:
            //TODO карта температур
            break;
        case HEIGHT:
            temp = (float) (z - minZ) / (maxZ - minZ + 1);
            tileShape.setFillColor(Color((1 - temp) * 255, (1 - temp) * 255, 255));
            break;
        case BIOMES:
            tileShape.setFillColor(type->getBiomeColor());
            break;
    }
    // координаты для отрисовки
    tileX = TILE_WIDTH * ((float) _x + (_y % 2 == 1 ? 0.5f : 0));
    drawTile(_window);
}

void Tile::drawTile(RenderWindow *_window) {
    tileShape.setPoint(0, Vector2f(tileX + TILE_WIDTH / 2, tileY + TILE_HEIGHT));
    tileShape.setPoint(1, Vector2f(tileX + TILE_WIDTH, tileY + TILE_HEIGHT * 3 / 4.f));
    tileShape.setPoint(2, Vector2f(tileX + TILE_WIDTH, tileY + TILE_HEIGHT / 4.f));
    tileShape.setPoint(3, Vector2f(tileX + TILE_WIDTH / 2, tileY));
    tileShape.setPoint(4, Vector2f(tileX, tileY + TILE_HEIGHT / 4.f));
    tileShape.setPoint(5, Vector2f(tileX, tileY + TILE_HEIGHT * 3 / 4.f));
    _window->draw(tileShape);
}

float Tile::getLatitude() {
    return latitude;
}

float Tile::getLongitude() {
    return longitude;
}

int Tile::getX() {
    return x;
}

int Tile::getY() {
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