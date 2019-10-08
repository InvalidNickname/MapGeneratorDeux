#include "TileGrid.h"

TileGrid::TileGrid() {
    grid = new std::vector<std::vector<Tile *> *>(MAP_WIDTH);
    for (uint16_t i = 0; i < MAP_WIDTH; i++) {
        grid->at(i) = new std::vector<Tile *>(MAP_HEIGHT);
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            grid->at(i)->at(j) = new Tile(i, j);
        }
    }
}

Tile *TileGrid::getTile(uint16_t x, uint16_t y) {
    return grid->at(x)->at(y);
}

Tile *TileGrid::getNeighbour(int direction, Tile *tile) {
    return getNeighbour(direction, tile->getX(), tile->getY());
}

Tile *TileGrid::getNeighbour(int direction, uint16_t x, uint16_t y) {
    if (y % 2 == 0) {
        switch (direction) {
            case 0:
                if (x > 0)
                    return getTile(x - 1, y);
                else
                    return getTile(MAP_WIDTH - 1, y);
            case 1:
                if (x > 0 && y < MAP_HEIGHT - 1)
                    return getTile(x - 1, y + 1);
                else if (y < MAP_HEIGHT - 1)
                    return getTile(MAP_WIDTH - 1, y + 1);
            case 2:
                if (y < MAP_HEIGHT - 1)
                    return getTile(x, y + 1);
            case 3:
                if (x < MAP_WIDTH - 1)
                    return getTile(x + 1, y);
                else if (x == MAP_WIDTH - 1)
                    return getTile(0, y);
            case 4:
                if (y > 0)
                    return getTile(x, y - 1);
            case 5:
                if (y > 0 && x > 0)
                    return getTile(x - 1, y - 1);
                else if (y > 0)
                    return getTile(MAP_WIDTH - 1, y - 1);
            default:
                return nullptr;
        }
    } else {
        switch (direction) {
            case 0:
                if (x > 0)
                    return getTile(x - 1, y);
                else
                    return getTile(MAP_WIDTH - 1, y);
            case 1:
                if (y < MAP_HEIGHT - 1)
                    return getTile(x, y + 1);
            case 2:
                if (y < MAP_HEIGHT - 1 && x < MAP_WIDTH - 1)
                    return getTile(x + 1, y + 1);
                else if (y < MAP_HEIGHT - 1)
                    return getTile(0, y + 1);
            case 3:
                if (x < MAP_WIDTH - 1)
                    return getTile(x + 1, y);
                else
                    return getTile(0, y);
            case 4:
                if (y > 0 && x < MAP_WIDTH - 1)
                    return getTile(x + 1, y - 1);
                else if (y > 0)
                    return getTile(0, y - 1);
            case 5:
                if (y > 0)
                    return getTile(x, y - 1);
            default:
                return nullptr;
        }
    }
}

int TileGrid::getMaxZ() {
    return maxZ;
}

void TileGrid::setMaxZ(int _maxZ) {
    maxZ = _maxZ;
}

int TileGrid::getMinZ() {
    return minZ;
}

void TileGrid::setMinZ(int _minZ) {
    minZ = _minZ;
}
