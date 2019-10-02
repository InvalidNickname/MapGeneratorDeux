#pragma once

#include "Tile.h"

class TileGrid {
  public:
    explicit TileGrid();

    Tile *getTile(int x, int y);

    Tile *getNeighbour(int direction, int x, int y);

    Tile *getNeighbour(int direction, Tile *tile);

    int getMaxZ();

    void setMaxZ(int maxZ);

    int getMinZ();

    void setMinZ(int minZ);

  private:
    int maxZ, minZ;

    std::vector<std::vector<Tile *> *> *grid;

};