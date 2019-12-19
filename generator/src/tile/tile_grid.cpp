#include "tile_grid.h"

TileGrid::TileGrid(Vector2u map_size) : size_(map_size) {
  grid_ = new vector<vector<Tile *> *>(map_size.x);
  river_map_ = new vector<vector<bool> *>(map_size.x);
  for (uint16_t i = 0; i < map_size.x; i++) {
    grid_->at(i) = new vector<Tile *>(map_size.y);
    river_map_->at(i) = new vector<bool>(map_size.y, false);
    for (uint16_t j = 0; j < map_size.y; j++) {
      grid_->at(i)->at(j) = new Tile({i, j});
    }
  }
}

Tile *TileGrid::GetTile(Vector2u pos) const {
  return grid_->at(pos.x)->at(pos.y);
}

Tile *TileGrid::GetNeighbour(int direction, Tile *tile) const {
  return GetNeighbour(direction, tile->pos_);
}

Tile *TileGrid::GetNeighbour(int direction, Vector2u pos) const {
  if (pos.y % 2 == 0) {
    switch (direction) {
      case 0:
        if (pos.x > 0)
          return GetTile({pos.x - 1, pos.y});
        else
          return GetTile({size_.x - 1u, pos.y});
      case 1:
        if (pos.x > 0 && pos.y < size_.y - 1u)
          return GetTile({pos.x - 1, pos.y + 1});
        else if (pos.y < size_.y - 1u)
          return GetTile({size_.x - 1u, pos.y + 1});
      case 2:
        if (pos.y < size_.y - 1u)
          return GetTile({pos.x, pos.y + 1});
      case 3:
        if (pos.x < size_.x - 1u)
          return GetTile({pos.x + 1, pos.y});
        else if (pos.x == size_.x - 1)
          return GetTile({0, pos.y});
      case 4:
        if (pos.y > 0)
          return GetTile({pos.x, pos.y - 1});
      case 5:
        if (pos.y > 0 && pos.x > 0)
          return GetTile({pos.x - 1, pos.y - 1});
        else if (pos.y > 0)
          return GetTile({size_.x - 1u, pos.y - 1});
      default:return nullptr;
    }
  } else {
    switch (direction) {
      case 0:
        if (pos.x > 0)
          return GetTile({pos.x - 1, pos.y});
        else
          return GetTile({size_.x - 1u, pos.y});
      case 1:
        if (pos.y < size_.y - 1u)
          return GetTile({pos.x, pos.y + 1});
      case 2:
        if (pos.y < size_.y - 1u && pos.x < size_.x - 1u)
          return GetTile({pos.x + 1, pos.y + 1});
        else if (pos.y < size_.y - 1u)
          return GetTile({0, pos.y + 1});
      case 3:
        if (pos.x < size_.x - 1u)
          return GetTile({pos.x + 1, pos.y});
        else
          return GetTile({0, pos.y});
      case 4:
        if (pos.y > 0 && pos.x < size_.x - 1u)
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

int TileGrid::GetMaxZ() const {
  return max_z_;
}

void TileGrid::SetMaxZ(int max_z) {
  max_z_ = max_z;
}

int TileGrid::GetMinZ() const {
  return min_z_;
}

void TileGrid::SetMinZ(int min_z) {
  min_z_ = min_z;
}

bool TileGrid::GetRiver(Vector2u pos) const {
  return river_map_->at(pos.x)->at(pos.y);
}

void TileGrid::SetRiver(Vector2u pos, bool isRiver) {
  river_map_->at(pos.x)->at(pos.y) = isRiver;
}

TileGrid::~TileGrid() {
  delete grid_;
  delete river_map_;
}
