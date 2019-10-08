#pragma once

#include <vector>

#include <screens/map/objects/tiles/Tile.h>
#include <screens/map/objects/tiles/TileGrid.h>
#include <utils/GenerationParameters.h>
#include <utils/Random.h>
#include <utils/PerlinNoise.h>

class Generator {
  public:
    TileGrid *generate();

  private:
    TileGrid *grid{nullptr};
    uint32_t oceanLevel{0};

    void raiseTerrain();

    void flattenTerrain();

    // определение максимальной, минимальной высоты и уровня моря
    void findZLimits();

    void setTemperature();

    void setLand();

    void flattenContinentBorders();

    void setTerrainLevel();

    void setMoisture();

    void setTerrainFromTileset();

    // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
    void deleteTilePaths(const string &type, const string &changeTo, Tile *tile);

    uint8_t countNeighboursWithType(const string &type, Tile *tile);
};
