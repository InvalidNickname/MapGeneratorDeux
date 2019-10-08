#pragma once

#include "Tile.h"

class TileGrid {
  public:
    explicit TileGrid();

    Tile *getTile(uint16_t x, uint16_t y);

    Tile *getNeighbour(int direction, uint16_t x, uint16_t y);

    Tile *getNeighbour(int direction, Tile *tile);

    int getMaxZ();

    void setMaxZ(int maxZ);

    int getMinZ();

    void setMinZ(int minZ);

  private:
    std::vector<std::vector<Tile *> *> *grid;
    int maxZ{0}, minZ{2147483647};

};