#include "Tile.h"

class TileGrid {
  public:
    explicit TileGrid(std::vector<std::vector<Tile *> *> *grid);

    Tile *getTile(int x, int y);

    Tile *getNeighbour(int direction, int x, int y);

  private:
    std::vector<std::vector<Tile *> *> *grid;

};