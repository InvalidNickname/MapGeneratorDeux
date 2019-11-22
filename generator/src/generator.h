#ifndef MGD_GENERATOR_SRC_GENERATOR_H
#define MGD_GENERATOR_SRC_GENERATOR_H

#include "tile/tile_grid.h"
#include "utils/random.h"
#include "utils/perlin_noise.h"

class Generator {
 public:
  TileGrid *Generate();

 private:
  TileGrid *grid_{nullptr};
  uint16_t ocean_level_{0}, land_border_;
  vector<vector<float>> factor_;
  uint16_t river_length_;

  void RaiseTerrain();

  void FlattenTerrain();

  // определение максимальной, минимальной высоты и уровня моря
  void FindZLimits();

  void SetTemperature();

  void SetLand();

  void FlattenContinentBorders();

  void SetTerrainLevel();

  void SetMoisture();

  void SetTerrainFromTileset();

  void SetRivers();

  void ContinueRiver(Vector2u pos);

  void DeleteRiver(Vector2u pos);

  // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
  void DeleteTilePaths(const string &type, const string &change_to, Tile *tile);

  uint8_t CountNeighboursWithType(const string &type, Tile *tile);
};

#endif
