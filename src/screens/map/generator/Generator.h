#include <vector>
#include <screens/map/objects/tiles/Tile.h>
#include <screens/map/objects/tiles/TileGrid.h>
#include "GenerationParameters.h"
#include <random>

class Generator {
  public:

    TileGrid *generate();

    Generator setSeed(int seed);

  private:
    TileGrid *grid{nullptr};
    int oceanLevel{0}, maxZ{0}, minZ{2147483647};
    default_random_engine engine;

    void setTerrainLevel();

    void flattenTerrain();

    void flattenContinentBorders();

    void setLand();

    // рекурсивное удаление гексов, имеющих только 2 соседей того же типа
    void deleteTilePaths(const String &type, const String &changeTo, Tile *tile);

    // определение максимальной, минимальной высоты и уровня моря
    void findZLimits();

    int countNeighboursWithType(const String &type, Tile *tile);

    void raiseTerrain();

    void setTerrainFromTileset();

    int random(int x, int y);
};
