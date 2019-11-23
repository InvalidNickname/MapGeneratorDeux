#include "generator.h"

TileGrid *Generator::Generate() {
  land_border_ = 0.07 * G::GetMapH();
  grid_ = new TileGrid({G::GetMapW(), G::GetMapH()});
  RaiseTerrain();
  FlattenTerrain();
  FindZLimits();
  SetTemperature();
  SetLand();
  FlattenContinentBorders();
  SetTerrainLevel();
  SetMoisture();
  SetTerrainFromTileset();
  SetRivers();
  return grid_;
}

void Generator::RaiseTerrain() {
  if (G::GetGeneratorType() == "best") {
    // общее количество клеток суши
    uint32_t land_budget = grid_->size_.y * grid_->size_.x;
    // количество начальных точек континентов
    uint16_t size = Random::Get().GetInt(40, 60);
    // количество точек в континенте
    uint16_t continent_size = land_budget / size;
    for (uint16_t i = 0; i < size; i++) {
      // определение центрального гекса континента
      auto prev = Vector2u(
          Random::Get().GetInt(0, grid_->size_.x - 1),
          Random::Get().GetInt(land_border_, G::GetMapH() - land_border_ - 1)
      );
      // построение континента вокруг центрального гекса
      for (uint16_t j = 0; j < continent_size; j++) {
        Tile *neighbour = grid_->GetNeighbour(Random::Get().GetInt(0, 6), prev);
        if (neighbour != nullptr) {
          float factor = 1;
          // если выбранный сосед за границей суши, уменьшается вероятность поднятия суши там
          if (neighbour->pos_.y < land_border_)
            factor = min(factor, (float) neighbour->pos_.y / land_border_);
          if (neighbour->pos_.y > grid_->size_.y - land_border_ - 1)
            factor = min(factor, (float) (grid_->size_.y - 1 - neighbour->pos_.y) / land_border_);
          if ((float) Random::Get().GetInt(10, 100) / 100.f < factor) {
            neighbour->IncreaseZ(1);
            if (neighbour->GetZ() > 0) {
              j--;
            }
          }
          prev = neighbour->pos_;
        } else {
          j--;
        }
      }
    }
  } else {
    PerlinNoise perlin_noise = PerlinNoise(Random::Get().GetSeed());
    for (uint16_t i = 0; i < grid_->size_.x; i++)
      for (uint16_t j = 0; j < grid_->size_.y; j++) {
        Tile *tile = grid_->GetTile({i, j});
        float z = 1;
        if (tile->pos_.y < land_border_) z = (float) tile->pos_.y / land_border_;
        if (tile->pos_.y > grid_->size_.y - land_border_ - 1) {
          z = (float) (grid_->size_.y - 1 - tile->pos_.y) / land_border_;
        }
        z *= (perlin_noise.Noise(
            0.01f * (float) i,
            0.01f * (float) j,
            grid_->size_.x * 0.01f,
            grid_->size_.y * 0.01f, 4) + 1) / 2.f;
        tile->SetZ(1000 * z);
      }
  }
}

// сглаживание суши, эрозия
void Generator::FlattenTerrain() {
  for (uint8_t n = 0; n < G::GetFlatness(); n++) {
    for (uint16_t i = 0; i < grid_->size_.x; i++)
      for (uint16_t j = 0; j < grid_->size_.y; j++) {
        Tile *tile = grid_->GetTile({i, j});
        for (uint8_t k = 0; k < 6; k++) {
          Tile *neighbour = grid_->GetNeighbour(k, {i, j});
          if (neighbour != nullptr)
            if (tile->GetZ() - neighbour->GetZ() > 3) {
              tile->IncreaseZ(-1);
              neighbour->IncreaseZ(1);
            }
        }
      }
  }
}

void Generator::FindZLimits() {
  // общая высота всех тайлов
  uint32_t terrain_mass = 0;
  for (uint16_t i = 0; i < grid_->size_.x; i++)
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      Tile *tile = grid_->GetTile({i, j});
      if (tile->GetZ() > grid_->GetMaxZ()) {
        grid_->SetMaxZ(tile->GetZ());
      }
      if (tile->GetZ() < grid_->GetMinZ()) {
        grid_->SetMinZ(tile->GetZ());
      }
      terrain_mass += tile->GetZ();
    }
  terrain_mass /= grid_->size_.y * grid_->size_.x;
  ocean_level_ = (float) terrain_mass * G::GetOceanLevel();
}

void Generator::SetTemperature() {
  PerlinNoise perlin_noise = PerlinNoise(Random::Get().GetSeed() * 2);
  for (uint16_t i = 0; i < grid_->size_.x; i++)
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      Tile *tile = grid_->GetTile({i, j});
      float temperature = 1 - tile->latitude_ / 90.f;
      temperature *= (perlin_noise.Noise(
          0.01f * (float) i,
          0.01f * (float) j,
          grid_->size_.x * 0.01f,
          grid_->size_.y * 0.01f, 4) + 1) / 2.f;
      if (tile->GetZ() > ocean_level_) {
        temperature *= 1 - (float) (tile->GetZ() - ocean_level_) / (float) (grid_->GetMaxZ() - ocean_level_);
      }
      temperature = pow(temperature, 1.f / 3);
      tile->SetTemperature(G::GetMinTemp() + temperature * (G::GetMaxTemp() - G::GetMinTemp()));
    }
}

// установка суши по уровню океана
void Generator::SetLand() {
  for (uint16_t i = 0; i < grid_->size_.x; i++)
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      Tile *tile = grid_->GetTile({i, j});
      if (tile->GetZ() > ocean_level_) {
        tile->SetType("GenLand");
      }
    }
}

// сглаживание границ континентов, удаление полосок тайлов
void Generator::FlattenContinentBorders() {
  for (uint8_t z = 0; z < 4; z++) {
    for (uint16_t i = 0; i < grid_->size_.x; i++)
      for (uint16_t j = 0; j < grid_->size_.y; j++) {
        Tile *tile = grid_->GetTile({i, j});
        if (tile->GetType()->type_name == "GenWater" && CountNeighboursWithType("GenWater", tile) <= 2) {
          DeleteTilePaths("GenWater", "GenLand", tile);
        } else if (tile->GetType()->type_name == "GenLand" &&
            CountNeighboursWithType("GenLand", tile) <= 2) {
          DeleteTilePaths("GenLand", "GenWater", tile);
        }
      }
  }
}

void Generator::SetTerrainLevel() {
  for (uint16_t i = 0; i < grid_->size_.x; i++)
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      Tile *tile = grid_->GetTile({i, j});
      float relative_elevation;
      if (tile->GetType()->above_sea_level) {
        relative_elevation = (float) (tile->GetZ() - ocean_level_) / (float) (grid_->GetMaxZ() - ocean_level_);
      } else {
        relative_elevation = (float) (ocean_level_ - tile->GetZ()) / (float) (ocean_level_ - grid_->GetMinZ());
      }
      if (relative_elevation > 0.35) {
        tile->SetLevel(Level::HIGH);
      } else if (relative_elevation > 0.2) {
        tile->SetLevel(Level::MEDIUM);
      } else if (relative_elevation > 0.05) {
        tile->SetLevel(Level::SMALL);
      } else {
        tile->SetLevel(Level::NO);
      }
    }
}

void Generator::SetMoisture() {
  PerlinNoise perlin_noise = PerlinNoise(Random::Get().GetSeed());
  float max_moisture = 0;
  for (uint16_t i = 0; i < grid_->size_.x; i++)
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      Tile *tile = grid_->GetTile({i, j});
      float moisture = 1 - tile->latitude_ / 90.f;
      moisture *= (perlin_noise.Noise(
          0.01f * (float) i,
          0.01f * (float) j,
          grid_->size_.x * 0.01f,
          grid_->size_.y * 0.01f, 4) + 1) / 2.f;
      tile->SetMoisture(G::GetMinMoisture() + moisture * (G::GetMaxMoisture() - G::GetMinMoisture()));
      if (moisture > max_moisture) max_moisture = moisture;
    }
}

void Generator::SetTerrainFromTileset() {
  for (uint16_t i = 0; i < Tileset::Get().GetSize(); i++) {
    Type *type = Tileset::Get().GetType(i);
    for (uint16_t j = 0; j < grid_->size_.x; j++)
      for (uint16_t k = 0; k < grid_->size_.y; k++) {
        Tile *tile = grid_->GetTile({j, k});
        if (tile->GetZ() > ocean_level_ == type->above_sea_level &&
            tile->GetTemperature() >= type->temperature_range->first &&
            tile->GetTemperature() <= type->temperature_range->second &&
            tile->GetMoisture() >= type->moisture_range->first &&
            tile->GetMoisture() <= type->moisture_range->second &&
            ((type->neighbour.empty()) || (CountNeighboursWithType(type->neighbour, tile) > 0))) {
          tile->SetType(type->type_name);
        }
      }
  }
}

void Generator::SetRivers() {
  factor_ = vector<vector<float>>(grid_->size_.x, vector<float>(grid_->size_.y, 0.05));
  for (uint16_t i = 0; i < grid_->size_.x; i++) {
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      Tile *tile = grid_->GetTile({i, j});
      if (!tile->GetType()->above_sea_level) {
        // под водой рек не бывает
        factor_[i][j] = 0;
      } else {
        factor_[i][j] *= sqrt((float) (tile->GetZ() - ocean_level_) / (float) (grid_->GetMaxZ() - ocean_level_));
        factor_[i][j] *= tile->GetMoisture();
      }
    }
  }
  for (uint16_t i = 0; i < grid_->size_.x; i++) {
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      auto random = (float) Random::Get().GetInt(0, 100) / 100.f;
      if (factor_[i][j] > random) {
        // в этой точке начинается река
        grid_->SetRiver({i, j}, true);
        river_length_ = 1;
        ContinueRiver({i, j});
      }
    }
  }
}

void Generator::ContinueRiver(Vector2u pos) {
  // находим соседний тайл с минимальной высотой
  int8_t min_dir = -1;
  float min_z = 2;
  for (uint8_t i = 0; i < 6; ++i) {
    Vector2u n_pos = grid_->GetNeighbour(i, pos)->pos_;
    // или земля с фактором выше 0, или вода
    if ((factor_[n_pos.x][n_pos.y] < min_z && factor_[n_pos.x][n_pos.y] > 0) ||
        !grid_->GetTile(n_pos)->GetType()->above_sea_level) {
      min_dir = i;
      min_z = factor_[n_pos.x][n_pos.y];
    }
  }
  if (min_dir > -1) {
    for (uint8_t i = 0; i < 6; ++i) {
      Vector2u n_pos = grid_->GetNeighbour(i, pos)->pos_;
      factor_[n_pos.x][n_pos.y] = 0;
    }
    if (grid_->GetNeighbour(min_dir, pos)->GetType()->above_sea_level) {
      Vector2u min_pos = grid_->GetNeighbour(min_dir, pos)->pos_;
      grid_->SetRiver(min_pos, true);
      river_length_++;
      ContinueRiver(min_pos);
    } else if (river_length_ == 1) {
      grid_->SetRiver(pos, false);
    }
  } else {
    // река не впадает в океан, удалить
    DeleteRiver(pos);
  }
}

void Generator::DeleteRiver(Vector2u pos) {
  factor_[pos.x][pos.y] = 0;
  grid_->SetRiver(pos, false);
  for (uint8_t i = 0; i < 6; ++i) {
    Vector2u tile_pos = grid_->GetNeighbour(i, pos)->pos_;
    if (grid_->GetRiver(tile_pos)) {
      DeleteRiver(tile_pos);
    }
  }
}

void Generator::DeleteTilePaths(const string &type, const string &change_to, Tile *tile) {
  tile->SetType(change_to);
  if (Tileset::Get().GetType(change_to)->above_sea_level) tile->SetZ(ocean_level_ + 1);
  else tile->SetZ(ocean_level_ - 1);
  if (CountNeighboursWithType(type, tile) <= 2)
    for (uint8_t i = 0; i < 6; i++) {
      Tile *neighbour = grid_->GetNeighbour(i, tile);
      if (neighbour != nullptr)
        if (neighbour->GetType()->type_name == type)
          DeleteTilePaths(type, change_to, neighbour);
    }
}

uint8_t Generator::CountNeighboursWithType(const string &type, Tile *tile) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < 6; i++)
    if (grid_->GetNeighbour(i, tile) != nullptr)
      if (grid_->GetNeighbour(i, tile)->GetType()->type_name == type)
        count++;
  return count;
}