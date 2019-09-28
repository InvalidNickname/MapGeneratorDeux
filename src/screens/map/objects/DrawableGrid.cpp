#include "DrawableGrid.h"
#include <iostream>

DrawableGrid::DrawableGrid() {
    // TODO вставить генератор
    auto *grid = new std::vector<std::vector<Tile *> *>(MAP_WIDTH, new std::vector<Tile *>(MAP_HEIGHT));
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            grid->at(i)->at(j) = new Tile(i, j);
        }
    }
    tileGrid = new TileGrid(grid);
    //TODO вставить генератор
}

void DrawableGrid::render(RenderWindow *_window, int x0, int y0, int x1, int y1) {
    if (y0 < 0) y0 = 0;
    if (y1 > MAP_HEIGHT) y1 = MAP_HEIGHT;

    if (x0 < 0) {
        for (int i = y0; i < y1; i++) {
            for (int j = 0; j < x1; j++)
                tileGrid->getTile(j, i)->render(_window, j, i);
            for (int j = MAP_WIDTH + x0; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_window, j - MAP_WIDTH, i);
        }
    } else if (x1 > MAP_WIDTH) {
        x1 = x1 % MAP_WIDTH;
        for (int i = y0; i < y1; i++) {
            for (int j = 0; j < x1; j++)
                tileGrid->getTile(j, i)->render(_window, j + MAP_WIDTH, i);
            for (int j = x0; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_window, j, i);
        }
    } else {
        for (int i = y0; i < y1; i++)
            for (int j = x0; j < x1; j++)
                tileGrid->getTile(j, i)->render(_window, j, i);
    }
}

Vector2i DrawableGrid::getTileByCoordinates(Vector2f coords) {
    float tempY = coords.y / (TILE_HEIGHT / 2.f);
    float relativeY = tempY - (int) (tempY / 1.5) * 1.5f;
    int tileY;

    float tempX = coords.x / (TILE_WIDTH);
    if (tempX < 0.5) tempX -= 1;
    float relativeX = fmod(tempX, 1);
    if (relativeX < 0) relativeX++;
    int tileX;

    if (relativeY >= 0.5 && relativeY < 1.5)
        // нажатие на центральную часть гекса
        tileY = (int) (tempY / 1.5);
    else {
        // нажатие на верхнюю или нижнюю часть гекса
        // четный ряд
        if (fmod(tempY, 1) > 0.5 && fmod(tempY, 1) < 1) {
            if (relativeX < 0.5) {
                if (relativeY / relativeX < 1)
                    tileY = (int) (tempY / 1.5) - 1;
                else tileY = (int) (tempY / 1.5);
            } else {
                if (relativeY < 1 - relativeX)
                    tileY = (int) (tempY / 1.5) - 1;
                else tileY = (int) (tempY / 1.5);
            }
        }
            // нечетный ряд
        else {
            if (relativeX < 0.5) {
                if (relativeY < 0.5 - relativeX)
                    tileY = (int) (tempY / 1.5) - 1;
                else tileY = (int) (tempY / 1.5);
            } else {
                if (relativeY / (relativeX - 0.5) < 1)
                    tileY = (int) (tempY / 1.5) - 1;
                else tileY = (int) (tempY / 1.5);
            }
        }
    }

    if (tileY % 2 == 0) {
        tileX = (int) tempX;
    } else {
        tileX = (int) (tempX - 0.5);
    }

    return {tileX, tileY};
}
