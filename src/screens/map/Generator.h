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
    int oceanLevel, maxZ, minZ;
    default_random_engine engine;

    void findOceanLevel();

    void setTerrainElevation();

    void flattenTerrain();

    void flattenContinentBorders();

    void setTerrainTypes();

    // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
    void deleteTilePaths(const String &type, const String &changeTo, Tile *tile);

    void findZLimits();

    int tileSurroundedByType(const String &type, Tile *tile);

    int tileSurroundedByArchtype(const String &archtype, Tile *tile);

    void raiseTerrain(int size);

    int random(int x, int y);
};
