#include "DrawableGrid.h"

DrawableGrid::DrawableGrid() {
    tileGrid = Generator(2).generate();
    maxZ = tileGrid->getMaxZ();
    minZ = tileGrid->getMinZ();
}

void DrawableGrid::render(RenderWindow *_window, MapMode mode, int x0, int y0, int x1, int y1) {
    if (y0 < 0) y0 = 0;
    if (y1 > MAP_HEIGHT) y1 = MAP_HEIGHT;

    if (x0 < 0) {
        for (int i = y0; i < y1; i++) {
            for (int j = 0; j < x1; j++)
                tileGrid->getTile(j, i)->render(_window, mode, j, i, maxZ, minZ);
            for (int j = MAP_WIDTH + x0; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_window, mode, j - MAP_WIDTH, i, maxZ, minZ);
        }
    } else if (x1 > MAP_WIDTH) {
        x1 = x1 % MAP_WIDTH;
        for (int i = y0; i < y1; i++) {
            for (int j = 0; j < x1; j++)
                tileGrid->getTile(j, i)->render(_window, mode, j + MAP_WIDTH, i, maxZ, minZ);
            for (int j = x0; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_window, mode, j, i, maxZ, minZ);
        }
    } else {
        for (int i = y0; i < y1; i++)
            for (int j = x0; j < x1; j++)
                tileGrid->getTile(j, i)->render(_window, mode, j, i, maxZ, minZ);
    }
}

Vector2i DrawableGrid::getTileByCoordinates(Vector2f coords) {
    // relative - положение точки внутри тайла, единица длины - сторона тайла

    float tempY = coords.y / (TILE_HEIGHT / 2.f);
    float relativeY = fmod(tempY, 1.5f);
    int tileY;

    float tempX = coords.x / (TILE_WIDTH);
    if (tempX < 0.5) tempX -= 1;
    float relativeX = fmod(tempX, 1.f);
    if (relativeX < 0) relativeX++;
    int tileX;

    if (relativeY >= 0.5 && relativeY < 1.5)
        // точка нахожится в центральной части гекса
        tileY = (int) (tempY / 1.5);
    else {
        // в верхней или нижней части гекса
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
        } else { // нечетный ряд, есть смещение гексов
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

    tileX = (int) (tempX - (tileY % 2 == 0 ? 0 : 0.5));

    return {tileX, tileY};
}
