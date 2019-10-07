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
    center->setSmooth(true);

    updateTexture(MapMode::NORMAL);

    sCenter.setTexture(center->getTexture());
    sCenter.scale(width / sCenter.getTexture()->getSize().x, height / sCenter.getTexture()->getSize().y);
    sCenter.setPosition(0, 0);

    sRight.setTexture(center->getTexture());
    sRight.scale(width / sRight.getTexture()->getSize().x, height / sRight.getTexture()->getSize().y);
    sRight.setPosition(width - TILE_WIDTH, 0);

    sLeft.setTexture(center->getTexture());
    sLeft.scale(width / sLeft.getTexture()->getSize().x, height / sLeft.getTexture()->getSize().y);
    sLeft.setPosition(-width + TILE_WIDTH, 0);

    selectedTile.setTexture(*AssetLoader::get().getTexture("selected_tile"));
    selectedTile.scale(TILE_WIDTH / selectedTile.getTexture()->getSize().x,
                       TILE_HEIGHT / selectedTile.getTexture()->getSize().y);
    selectedTile.setPosition(-100, -100);
}

void DrawableGrid::renderTexture(RenderTarget *_target, MapMode mode, int x0, int x1) {
    if (prev != mode) {
        updateTexture(mode);
        prev = mode;
    }
    _target->draw(sCenter);
    if (x1 > MAP_WIDTH) _target->draw(sRight);
    if (x0 < 0) _target->draw(sLeft);

    renderSelectedTile(_target);
}

void DrawableGrid::renderVector(RenderTarget *_target, MapMode mode, Vector2i lowerLeft, Vector2i upperRight) {
    if (lowerLeft.y < 0) lowerLeft.y = 0;
    if (upperRight.y > MAP_HEIGHT) upperRight.y = MAP_HEIGHT;
    if (lowerLeft.x < 0) {
        for (int i = lowerLeft.y; i < upperRight.y; i++) {
            for (int j = 0; j < upperRight.x; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j, i, maxZ, minZ);
            for (int j = MAP_WIDTH + lowerLeft.x; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j - MAP_WIDTH, i, maxZ, minZ);
        }
    } else if (upperRight.x > MAP_WIDTH) {
        upperRight.x = upperRight.x % MAP_WIDTH;
        for (int i = lowerLeft.y; i < upperRight.y; i++) {
            for (int j = 0; j < upperRight.x; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j + MAP_WIDTH, i, maxZ, minZ);
            for (int j = lowerLeft.x; j < MAP_WIDTH; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j, i, maxZ, minZ);
        }
    } else {
        for (int i = lowerLeft.y; i < upperRight.y; i++)
            for (int j = lowerLeft.x; j < upperRight.x; j++)
                tileGrid->getTile(j, i)->render(_target, mode, j, i, maxZ, minZ);
    }

    renderSelectedTile(_target);
}

void DrawableGrid::updateTexture(MapMode mode) {
    center->clear(Color::Transparent);
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++)
            tileGrid->getTile(i, j)->render(center, mode, i, j, maxZ, minZ);
    }
    center->display();
}

void DrawableGrid::renderSelectedTile(RenderTarget *_target) {
    if (selected.x >= 0 && selected.y >= 0) {
        selectedTile.setPosition(tileGrid->getTile(selected.x, selected.y)->getTileX(),
                                 tileGrid->getTile(selected.x, selected.y)->getTileY());
        _target->draw(selectedTile);
    }
}

void DrawableGrid::updateSelection(Vector2f position) {
    Vector2i tile = getTileByCoordinates(position);
    tile.x = tile.x > MAP_WIDTH - 1 ? tile.x - MAP_WIDTH : (tile.x < 0 ? MAP_WIDTH + tile.x : tile.x);
    if (tile.y >= 0 && tile.y < MAP_HEIGHT) {
        selected = tile;
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
