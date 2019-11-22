#ifndef MGD_GENERATOR_SRC_TILE_TILE_GRID_H
#define MGD_GENERATOR_SRC_TILE_TILE_GRID_H

#include "tile.h"

using namespace std;

class TileGrid {
 public:
  const Vector2<uint16_t> size_;

  explicit TileGrid(Vector2u map_size);

  [[nodiscard]] Tile *GetTile(Vector2u pos) const;

  [[nodiscard]] Tile *GetNeighbour(int direction, Vector2u pos) const;

  [[nodiscard]] Tile *GetNeighbour(int direction, Tile *tile) const;

  [[nodiscard]] int GetMaxZ() const;

  void SetMaxZ(int max_z);

  [[nodiscard]] int GetMinZ() const;

  void SetMinZ(int min_z);

  void SetRiver(Vector2u pos, bool isRiver);

  [[nodiscard]] bool GetRiver(Vector2u pos) const;

 private:
  vector<vector<Tile *> *> *grid_;
  vector<vector<bool> *> *river_map_;
  int max_z_{INT32_MIN}, min_z_{INT32_MAX};
};

#endif