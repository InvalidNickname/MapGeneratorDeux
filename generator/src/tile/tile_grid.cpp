#include "tile_grid.h"

TileGrid::TileGrid() {
  grid_ = new std::vector<std::vector<Tile *> *>(G::GetMapW());
  for (uint16_t i = 0; i < G::GetMapW(); i++) {
    grid_->at(i) = new std::vector<Tile *>(G::GetMapH());
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      grid_->at(i)->at(j) = new Tile({i, j});
    }
  }
}

Tile *TileGrid::GetTile(Vector2u pos) {
  return grid_->at(pos.x)->at(pos.y);
}

Tile *TileGrid::GetNeighbour(int direction, Tile *tile) {
  return GetNeighbour(direction, tile->pos_);
}

Tile *TileGrid::GetNeighbour(int direction, Vector2u pos) {
  if (pos.y % 2 == 0) {
    switch (direction) {
      case 0:
        if (pos.x > 0)
          return GetTile({pos.x - 1, pos.y});
        else
          return GetTile({G::GetMapW() - 1u, pos.y});
      case 1:
        if (pos.x > 0 && pos.y < G::GetMapH() - 1)
          return GetTile({pos.x - 1, pos.y + 1});
        else if (pos.y < G::GetMapH() - 1)
          return GetTile({G::GetMapW() - 1u, pos.y + 1});
      case 2:
        if (pos.y < G::GetMapH() - 1)
          return GetTile({pos.x, pos.y + 1});
      case 3:
        if (pos.x < G::GetMapW() - 1)
          return GetTile({pos.x + 1, pos.y});
        else if (pos.x == G::GetMapW() - 1)
          return GetTile({0, pos.y});
      case 4:
        if (pos.y > 0)
          return GetTile({pos.x, pos.y - 1});
      case 5:
        if (pos.y > 0 && pos.x > 0)
          return GetTile({pos.x - 1, pos.y - 1});
        else if (pos.y > 0)
          return GetTile({G::GetMapW() - 1u, pos.y - 1});
      default:return nullptr;
    }
  } else {
    switch (direction) {
      case 0:
        if (pos.x > 0)
          return GetTile({pos.x - 1, pos.y});
        else
          return GetTile({G::GetMapW() - 1u, pos.y});
      case 1:
        if (pos.y < G::GetMapH() - 1)
          return GetTile({pos.x, pos.y + 1});
      case 2:
        if (pos.y < G::GetMapH() - 1 && pos.x < G::GetMapW() - 1)
          return GetTile({pos.x + 1, pos.y + 1});
        else if (pos.y < G::GetMapH() - 1)
          return GetTile({0, pos.y + 1});
      case 3:
        if (pos.x < G::GetMapW() - 1)
          return GetTile({pos.x + 1, pos.y});
        else
          return GetTile({0, pos.y});
      case 4:
        if (pos.y > 0 && pos.x < G::GetMapW() - 1)
          return GetTile({pos.x + 1, pos.y - 1});
        else if (pos.y > 0)
          return GetTile({0, pos.y - 1});
      case 5:
        if (pos.y > 0)
          return GetTile({pos.x, pos.y - 1});
      default:return nullptr;
    }
  }
}

int TileGrid::GetMaxZ() {
  return max_z_;
}

void TileGrid::SetMaxZ(int max_z) {
  max_z_ = max_z;
}

int TileGrid::GetMinZ() {
  return min_z_;
}

void TileGrid::SetMinZ(int min_z) {
  min_z_ = min_z;
}
