#include <vector>
#include <random>

#include <screens/map/objects/tiles/Tile.h>
#include <screens/map/objects/tiles/TileGrid.h>
#include "GenerationParameters.h"

class Generator {
  public:
    TileGrid *generate();

    Generator setSeed(int seed);

  private:
    TileGrid *grid{nullptr};
    int oceanLevel{0};
    default_random_engine engine;

    void raiseTerrain();

    void flattenTerrain();

    // определение максимальной, минимальной высоты и уровня моря
    void findZLimits();

    void setLand();

    void flattenContinentBorders();

    void setTerrainLevel();

    void setTerrainFromTileset();

    // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
    void deleteTilePaths(const String &type, const String &changeTo, Tile *tile);

    int countNeighboursWithType(const String &type, Tile *tile);

    int random(int x, int y);
};
