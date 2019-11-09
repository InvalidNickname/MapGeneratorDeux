#pragma once

#include "Tile.h"

class TileGrid {
 public:
  explicit TileGrid();

  Tile *getTile(Vector2u pos);

  Tile *getNeighbour(int direction, Vector2u pos);

  Tile *getNeighbour(int direction, Tile *tile);

  int getMaxZ();

  void setMaxZ(int _max_z);

  int getMinZ();

  void setMinZ(int _min_z);

 private:
  std::vector<std::vector<Tile *> *> *grid;
  int max_z{INT32_MIN}, min_z{INT32_MAX};

};