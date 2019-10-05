#pragma once

#include <vector>

#include <screens/map/objects/tiles/Tile.h>
#include <screens/map/objects/tiles/TileGrid.h>
#include <utils/GenerationParameters.h>
#include <utils/Random.h>

class Generator {
  public:
    TileGrid *generate();

  private:
    TileGrid *grid{nullptr};
    int oceanLevel{0};

    void raiseTerrain();

    void flattenTerrain();

    // определение максимальной, минимальной высоты и уровня моря
    void findZLimits();

    void setTemperature();

    void setLand();

    void flattenContinentBorders();

    void setTerrainLevel();

    void setTerrainFromTileset();

    // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
    void deleteTilePaths(const String &type, const String &changeTo, Tile *tile);

    int countNeighboursWithType(const String &type, Tile *tile);
};
