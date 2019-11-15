#include "TileGrid.h"

TileGrid::TileGrid() {
  grid = new std::vector<std::vector<Tile *> *>(G::GetMapW());
  for (uint16_t i = 0; i < G::GetMapW(); i++) {
    grid->at(i) = new std::vector<Tile *>(G::GetMapH());
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      grid->at(i)->at(j) = new Tile({i, j});
    }
  }
}

Tile *TileGrid::getTile(Vector2u pos) {
  return grid->at(pos.x)->at(pos.y);
}

Tile *TileGrid::getNeighbour(int direction, Tile *tile) {
  return getNeighbour(direction, tile->pos);
}

Tile *TileGrid::getNeighbour(int direction, Vector2u pos) {
  if (pos.y % 2 == 0) {
    switch (direction) {
      case 0:
        if (pos.x > 0)
          return getTile({pos.x - 1, pos.y});
        else
          return getTile({G::GetMapW() - 1u, pos.y});
      case 1:
        if (pos.x > 0 && pos.y < G::GetMapH() - 1)
          return getTile({pos.x - 1, pos.y + 1});
        else if (pos.y < G::GetMapH() - 1)
          return getTile({G::GetMapW() - 1u, pos.y + 1});
      case 2:
        if (pos.y < G::GetMapH() - 1)
          return getTile({pos.x, pos.y + 1});
      case 3:
        if (pos.x < G::GetMapW() - 1)
          return getTile({pos.x + 1, pos.y});
        else if (pos.x == G::GetMapW() - 1)
          return getTile({0, pos.y});
      case 4:
        if (pos.y > 0)
          return getTile({pos.x, pos.y - 1});
      case 5:
        if (pos.y > 0 && pos.x > 0)
          return getTile({pos.x - 1, pos.y - 1});
        else if (pos.y > 0)
          return getTile({G::GetMapW() - 1u, pos.y - 1});
      default:return nullptr;
    }
  } else {
    switch (direction) {
      case 0:
        if (pos.x > 0)
          return getTile({pos.x - 1, pos.y});
        else
          return getTile({G::GetMapW() - 1u, pos.y});
      case 1:
        if (pos.y < G::GetMapH() - 1)
          return getTile({pos.x, pos.y + 1});
      case 2:
        if (pos.y < G::GetMapH() - 1 && pos.x < G::GetMapW() - 1)
          return getTile({pos.x + 1, pos.y + 1});
        else if (pos.y < G::GetMapH() - 1)
          return getTile({0, pos.y + 1});
      case 3:
        if (pos.x < G::GetMapW() - 1)
          return getTile({pos.x + 1, pos.y});
        else
          return getTile({0, pos.y});
      case 4:
        if (pos.y > 0 && pos.x < G::GetMapW() - 1)
          return getTile({pos.x + 1, pos.y - 1});
        else if (pos.y > 0)
          return getTile({0, pos.y - 1});
      case 5:
        if (pos.y > 0)
          return getTile({pos.x, pos.y - 1});
      default:return nullptr;
    }
  }
}

int TileGrid::getMaxZ() {
  return max_z;
}

void TileGrid::setMaxZ(int _max_z) {
  max_z = _max_z;
}

int TileGrid::getMinZ() {
  return min_z;
}

void TileGrid::setMinZ(int _min_z) {
  min_z = _min_z;
}
