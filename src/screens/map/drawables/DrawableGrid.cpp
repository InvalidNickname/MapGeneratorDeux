#include "DrawableGrid.h"

DrawableGrid::DrawableGrid() {
    tileGrid = Generator().generate();

    maxZ = tileGrid->getMaxZ();
    minZ = tileGrid->getMinZ();

    float height = 0.25f * TILE_HEIGHT * (3 * MAP_HEIGHT);
    float width = TILE_WIDTH * (0.5f + MAP_WIDTH);
    float camX = width / 2;
    float camY = height / 2;

    View view;
    view.setCenter(camX, camY);
    view.setSize(width, height);

    center = new RenderTexture();
    center->create(Texture::getMaximumSize() / 2, (Texture::getMaximumSize() / 2) / 300 * 190);
    center->setView(view);

    updateTexture(MapMode::NORMAL);

    sCenter.setTexture(center->getTexture());
    sCenter.scale(width / sCenter.getTexture()->getSize().x, height / sCenter.getTexture()->getSize().y);
    sCenter.setPosition(0, 0);

    sRight.setTexture(center->getTexture());
    sRight.scale(width / sRight.getTexture()->getSize().x, height / sRight.getTexture()->getSize().y);
    sRight.setPosition(width - 0.5f * TILE_WIDTH, 0);

    sLeft.setTexture(center->getTexture());
    sLeft.scale(width / sLeft.getTexture()->getSize().x, height / sLeft.getTexture()->getSize().y);
    sLeft.setPosition(-width + 0.5f * TILE_WIDTH, 0);

    selectedTile.setTexture(*AssetLoader::get().getTexture("selected_tile"));
    selectedTile.scale(TILE_WIDTH / selectedTile.getTexture()->getSize().x,
                       TILE_HEIGHT / selectedTile.getTexture()->getSize().y);
}

void DrawableGrid::renderTexture(RenderTarget *_target, MapMode mode, int x0, int x1) {
    if (prev != mode) {
        updateTexture(mode);
        prev = mode;
    }
    _target->draw(sCenter);
    if (x1 > MAP_WIDTH) _target->draw(sRight);
    if (x0 < 0) _target->draw(sLeft);

    renderSelectedTile(_target, x0, x1);
}

void DrawableGrid::renderVector(RenderTarget *_target, MapMode mode, Vector2i lowerLeft, Vector2i upperRight) {
    if (lowerLeft.y < 0) lowerLeft.y = 0;
    if (upperRight.y > MAP_HEIGHT) upperRight.y = MAP_HEIGHT;
    if (lowerLeft.x < 0) {
        for (int i = lowerLeft.y; i < upperRight.y; i++) {
            for (int j = 0; j < upperRight.x; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j, i, maxZ, minZ);
            for (int j = lowerLeft.x; j < 0; j++)
                tileGrid->getTile(j + MAP_WIDTH, i)->render(_target, mode, j, i, maxZ, minZ);
        }
    } else if (upperRight.x > MAP_WIDTH) {
        upperRight.x = upperRight.x % MAP_WIDTH;
        for (int i = lowerLeft.y; i < upperRight.y; i++) {
            for (int j = MAP_WIDTH; j < upperRight.x + MAP_WIDTH; j++)
                tileGrid->getTile(j - MAP_WIDTH, i)->render(_target, mode, j, i, maxZ, minZ);
            for (int j = lowerLeft.x; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j, i, maxZ, minZ);
        }
    } else {
        for (int i = lowerLeft.y; i < upperRight.y; i++)
            for (int j = lowerLeft.x; j < upperRight.x; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j, i, maxZ, minZ);
    }

    renderSelectedTile(_target, lowerLeft.x, upperRight.x);
}

void DrawableGrid::updateTexture(MapMode mode) {
    center->clear(Color::Transparent);
    for (uint16_t i = 0; i < MAP_WIDTH; i++) {
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            tileGrid->getTile(i, j)->render(center, mode, i, j, maxZ, minZ);
        }
    }
    center->display();
}

#include <iostream>

void DrawableGrid::renderSelectedTile(RenderTarget *_target, int x0, int x1) {
    if (selected.x >= 0 && selected.y >= 0) {
        float tileY = TILE_HEIGHT * (selected.y - (float) (selected.y / 2) / 2 - (selected.y % 2 == 1 ? 0.25f : 0));
        float tileX = TILE_WIDTH * (selected.x + (selected.y % 2 == 1 ? 0.5f : 0));
        if (x0 < 0 && (selected.x < 0 || selected.x >= x1)) {
            selectedTile.setPosition(tileX - TILE_WIDTH * MAP_WIDTH, tileY);
        } else if (x1 > MAP_WIDTH && selected.x < x1 % MAP_WIDTH) {
            selectedTile.setPosition(tileX + TILE_WIDTH * MAP_WIDTH, tileY);
        } else {
            selectedTile.setPosition(tileX, tileY);
        }
        _target->draw(selectedTile);
    }
}

void DrawableGrid::updateSelection(Vector2f position) {
    selected = getTileByCoordinates(position);
    // если клик на тайл на боковой карте - перенести его координаты на основную
    if (selected.x > MAP_WIDTH - 1) selected.x = selected.x - MAP_WIDTH;
    if (selected.x < 0) selected.x = MAP_WIDTH + selected.x;
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
