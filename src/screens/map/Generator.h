#include <vector>
#include <screens/map/objects/tiles/Tile.h>
#include "objects/tiles/TileGrid.h"
#include "MapParameters.h"
#include <random>

class Generator {
  public:
    explicit Generator(int seed);

    TileGrid *generate();

  private:
    TileGrid *grid;
    int continentSize;
    int oceanLevel, maxZ{0}, minZ{2147483647};
    default_random_engine engine;

    void setTerrainLevel();

    void flattenTerrain();

    void flattenContinentBorders();

    void setTerrainTypes();

    // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
    void deleteTilePaths(const String &type, const String &changeTo, Tile *tile);

    // определение максимальной, минимальной высоты и уровня моря
    void findZLimits();

    int countNeighboursWithType(const String &type, Tile *tile);

    void raiseTerrain(int size);

    void setTerrainFromTileset();

    int random(int x, int y);
};
