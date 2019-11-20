#include "generator.h"

TileGrid *Generator::Generate() {
  grid_ = new TileGrid();
  RaiseTerrain();
  FlattenTerrain();
  FindZLimits();
  SetTemperature();
  SetLand();
  FlattenContinentBorders();
  SetTerrainLevel();
  SetMoisture();
  SetTerrainFromTileset();
  return grid_;
}

void Generator::RaiseTerrain() {
  if (G::GetGeneratorType() == "best") {
    // общее количество клеток суши
    int land_budget = G::GetMapH() * G::GetMapW();
    // количество начальных точек континентов
    int size = Random::Get().GetInt(40, 60);
    // количество точек в континенте
    int continent_size = land_budget / size;
    for (int i = 0; i < size; i++) {
      // определение центрального гекса континента
      auto prev = Vector2u(
          Random::Get().GetInt(0, G::GetMapW() - 1),
          Random::Get().GetInt(G::GetLandBorder(), G::GetMapH() - G::GetLandBorder() - 1)
      );
      // построение континента вокруг центрального гекса
      for (int j = 0; j < continent_size; j++) {
        Tile *neighbour = grid_->GetNeighbour(Random::Get().GetInt(0, 6), prev);
        if (neighbour != nullptr) {
          float factor = 1;
          // если выбранный сосед за границей суши, уменьшается вероятность поднятия суши там
          if (neighbour->pos_.y < G::GetLandBorder())
            factor = min(factor, (float) neighbour->pos_.y / G::GetLandBorder());
          if (neighbour->pos_.y > G::GetMapH() - G::GetLandBorder() - 1)
            factor = min(factor, (float) (G::GetMapH() - 1 - neighbour->pos_.y) / G::GetLandBorder());
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
    for (uint16_t i = 0; i < G::GetMapW(); i++)
      for (uint16_t j = 0; j < G::GetMapH(); j++) {
        Tile *tile = grid_->GetTile({i, j});
        float z = 1;
        if (tile->pos_.y < G::GetLandBorder()) z = (float) tile->pos_.y / G::GetLandBorder();
        if (tile->pos_.y > G::GetMapH() - G::GetLandBorder() - 1) {
          z = (float) (G::GetMapH() - 1 - tile->pos_.y) / G::GetLandBorder();
        }
        z *= (perlin_noise.Noise(
            0.01f * (float) i,
            0.01f * (float) j,
            G::GetMapW() * 0.01f,
            G::GetMapH() * 0.01f, 4) + 1) / 2.f;
        tile->SetZ(1000 * z);
      }
  }
}

// сглаживание суши, эрозия
void Generator::FlattenTerrain() {
  for (uint16_t i = 0; i < G::GetMapW(); i++)
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
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

void Generator::FindZLimits() {
  // общая высота всех тайлов
  int terrain_mass = 0;
  for (uint16_t i = 0; i < G::GetMapW(); i++)
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      Tile *tile = grid_->GetTile({i, j});
      if (tile->GetZ() > grid_->GetMaxZ()) {
        grid_->SetMaxZ(tile->GetZ());
      }
      if (tile->GetZ() < grid_->GetMinZ()) {
        grid_->SetMinZ(tile->GetZ());
      }
      terrain_mass += tile->GetZ();
    }
  terrain_mass /= (G::GetMapH() * G::GetMapW());
  ocean_level_ = (float) terrain_mass * G::GetOceanLevel();
}

void Generator::SetTemperature() {
  PerlinNoise perlin_noise = PerlinNoise(Random::Get().GetSeed() * 2);
  for (uint16_t i = 0; i < G::GetMapW(); i++)
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      Tile *tile = grid_->GetTile({i, j});
      float temperature = 1 - tile->GetLatitude() / 90.f;
      temperature *= (perlin_noise.Noise(
          0.01f * (float) i,
          0.01f * (float) j,
          G::GetMapW() * 0.01f,
          G::GetMapH() * 0.01f, 4) + 1) / 2.f;
      if (tile->GetZ() > ocean_level_) {
        temperature *= 1 - (float) (tile->GetZ() - ocean_level_) / (float) (grid_->GetMaxZ() - ocean_level_);
      }
      temperature = pow(temperature, 1.f / 3);
      tile->SetTemperature(G::GetMinTemp() + temperature * (G::GetMaxTemp() - G::GetMinTemp()));
    }
}

// установка суши по уровню океана
void Generator::SetLand() {
  for (uint16_t i = 0; i < G::GetMapW(); i++)
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      Tile *tile = grid_->GetTile({i, j});
      if (tile->GetZ() > ocean_level_) {
        tile->SetType("GenLand");
      }
    }
}

// сглаживание границ континентов, удаление полосок тайлов
void Generator::FlattenContinentBorders() {
  for (uint8_t z = 0; z < 4; z++) {
    for (uint16_t i = 0; i < G::GetMapW(); i++)
      for (uint16_t j = 0; j < G::GetMapH(); j++) {
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
  for (uint16_t i = 0; i < G::GetMapW(); i++)
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
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
  for (uint16_t i = 0; i < G::GetMapW(); i++)
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      Tile *tile = grid_->GetTile({i, j});
      float moisture = 1 - tile->GetLatitude() / 90.f;
      moisture *= (perlin_noise.Noise(
          0.01f * (float) i,
          0.01f * (float) j,
          G::GetMapW() * 0.01f,
          G::GetMapH() * 0.01f, 4) + 1) / 2.f;
      tile->SetMoisture(moisture);
      if (moisture > max_moisture) max_moisture = moisture;
    }
}

void Generator::SetTerrainFromTileset() {
  for (uint16_t i = 0; i < Tileset::Get().GetSize(); i++) {
    Type *type = Tileset::Get().GetType(i);
    for (uint16_t j = 0; j < G::GetMapW(); j++)
      for (uint16_t k = 0; k < G::GetMapH(); k++) {
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