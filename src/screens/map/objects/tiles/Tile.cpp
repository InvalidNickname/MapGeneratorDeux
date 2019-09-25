#include "Tile.h"

Tile::Tile(int x, int y) : x(x), y(y) {

}

void Tile::render(RenderWindow *_window, int _x, int _y) {
    // координаты для отрисовки
    tileX = ((float) _x + (_y % 2 == 1 ? 0.5f : 0)) * MapParameters::TILE_WIDTH;
    tileY = (float) y * MapParameters::TILE_HEIGHT - (float) (y >> 1) * MapParameters::TILE_HEIGHT / 2 -
            (y % 2 == 1 ? 0.25f * MapParameters::TILE_HEIGHT : 0);
    drawTile(_window);
}

void Tile::drawTile(RenderWindow *_window) {
    ConvexShape tile;
    tile.setPointCount(6);
    tile.setPoint(0, Vector2f(tileX + MapParameters::TILE_WIDTH / 2, tileY + MapParameters::TILE_HEIGHT));
    tile.setPoint(1, Vector2f(tileX + MapParameters::TILE_WIDTH, tileY + MapParameters::TILE_HEIGHT * 3 / 4));
    tile.setPoint(2, Vector2f(tileX + MapParameters::TILE_WIDTH, tileY + MapParameters::TILE_HEIGHT / 4));
    tile.setPoint(3, Vector2f(tileX + MapParameters::TILE_WIDTH / 2, tileY));
    tile.setPoint(4, Vector2f(tileX, tileY + MapParameters::TILE_HEIGHT / 4));
    tile.setPoint(5, Vector2f(tileX, tileY + MapParameters::TILE_HEIGHT * 3 / 4));
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

Type Tile::getType() {
    return type;
}
