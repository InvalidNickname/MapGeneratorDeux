#include "Tile.h"

Tile::Tile(int x, int y) : x(x), y(y) {
    tileY = TILE_HEIGHT * ((float) y - (float) (y / 2) / 2 - (y % 2 == 1 ? 0.25f : 0));
}

void Tile::render(RenderWindow *_window, int _x, int _y) {
    // координаты для отрисовки
    tileX = TILE_WIDTH * ((float) _x + (_y % 2 == 1 ? 0.5f : 0));
    drawTile(_window);
}

void Tile::drawTile(RenderWindow *_window) {
    ConvexShape tile;
    tile.setPointCount(6);
    tile.setPoint(0, Vector2f(tileX + TILE_WIDTH / 2, tileY + TILE_HEIGHT));
    tile.setPoint(1, Vector2f(tileX + TILE_WIDTH, tileY + TILE_HEIGHT * 3 / 4.f));
    tile.setPoint(2, Vector2f(tileX + TILE_WIDTH, tileY + TILE_HEIGHT / 4.f));
    tile.setPoint(3, Vector2f(tileX + TILE_WIDTH / 2, tileY));
    tile.setPoint(4, Vector2f(tileX, tileY + TILE_HEIGHT / 4.f));
    tile.setPoint(5, Vector2f(tileX, tileY + TILE_HEIGHT * 3 / 4.f));
    _window->draw(tile);
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