#include "TileGrid.h"

TileGrid::TileGrid(std::vector<std::vector<Tile *> *> *grid) : grid(grid) {}

Tile *TileGrid::getTile(int x, int y) {
    return grid->at(x)->at(y);
}

Tile *TileGrid::getNeighbour(int direction, int x, int y) {
    if (y % 2 == 0) {
        switch (direction) {
            case 0:
                if (x > 0)
                    return grid->at(x - 1)->at(y);
                else
                    return grid->at(MAP_WIDTH - 1)->at(y);
            case 1:
                if (x > 0 && y < MAP_HEIGHT - 1)
                    return grid->at(x - 1)->at(y + 1);
                else if (y < MAP_HEIGHT - 1)
                    return grid->at(MAP_WIDTH - 1)->at(y + 1);
            case 2:
                if (y < MAP_HEIGHT - 1)
                    return grid->at(x)->at(y + 1);
            case 3:
                if (x < MAP_WIDTH - 1)
                    return grid->at(x + 1)->at(y);
                else if (x == MAP_WIDTH - 1)
                    return grid->at(0)->at(y);
            case 4:
                if (y > 0)
                    return grid->at(x)->at(y - 1);
            case 5:
                if (y > 0 && x > 0)
                    return grid->at(x - 1)->at(y - 1);
                else if (y > 0)
                    return grid->at(MAP_WIDTH - 1)->at(y - 1);
        }
    } else {
        switch (direction) {
            case 0:
                if (x > 0)
                    return grid->at(x - 1)->at(y);
                else
                    return grid->at(MAP_WIDTH - 1)->at(y);
            case 1:
                if (y < MAP_HEIGHT - 1)
                    return grid->at(x)->at(y + 1);
            case 2:
                if (y < MAP_HEIGHT - 1 && x < MAP_WIDTH - 1)
                    return grid->at(x + 1)->at(y + 1);
                else if (y < MAP_HEIGHT - 1)
                    return grid->at(0)->at(y + 1);
            case 3:
                if (x < MAP_WIDTH - 1)
                    return grid->at(x + 1)->at(y);
                else
                    return grid->at(0)->at(y);
            case 4:
                if (y > 0 && x < MAP_WIDTH - 1)
                    return grid->at(x + 1)->at(y - 1);
                else if (y > 0)
                    return grid->at(0)->at(y - 1);
            case 5:
                if (y > 0)
                    return grid->at(x)->at(y - 1);
        }
    }
    return nullptr;
}
