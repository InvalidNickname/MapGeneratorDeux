#include <screens/map/objects/tiles/type/Tileset.h>
#include "Tile.h"

Tile::Tile(int x, int y) : x(x), y(y) {
    tileY = TILE_HEIGHT * ((float) y - (float) (y / 2) / 2 - (y % 2 == 1 ? 0.25f : 0));
    shape = VertexArray(TriangleFan, 8);
}

void Tile::render(RenderWindow *_window, MapMode mode, int _x, int _y, int maxZ, int minZ) {
    float temp;
    Color color;
    switch (mode) {
        case NORMAL:
            color = type->getBaseColor(level);
            break;
        case TEMPERATURE:
            //TODO карта температур
            break;
        case HEIGHT:
            temp = (float) (z - minZ) / ((float) maxZ - (float) minZ + 1.f);
            color = Color((1 - temp) * 255, (1 - temp) * 255, 255);
            break;
        case BIOMES:
            color = type->getBiomeColor();
            break;
    }
    // координаты для отрисовки
    tileX = TILE_WIDTH * ((float) _x + (_y % 2 == 1 ? 0.5f : 0));
    drawTile(_window, color);
}

void Tile::drawTile(RenderWindow *_window, Color color) {
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
    _window->draw(shape);
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