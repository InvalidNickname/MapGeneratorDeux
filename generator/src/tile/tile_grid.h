#ifndef MGD_GENERATOR_SRC_TILE_TILE_GRID_H
#define MGD_GENERATOR_SRC_TILE_TILE_GRID_H

#include "tile.h"

class TileGrid {
 public:
  explicit TileGrid();

  Tile *GetTile(Vector2u pos);

  Tile *GetNeighbour(int direction, Vector2u pos);

  Tile *GetNeighbour(int direction, Tile *tile);

  int GetMaxZ();

  void SetMaxZ(int max_z);

  int GetMinZ();

  void SetMinZ(int min_z);

 private:
  std::vector<std::vector<Tile *> *> *grid_;
  int max_z_{INT32_MIN}, min_z_{INT32_MAX};
};

#endif