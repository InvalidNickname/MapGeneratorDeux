#include "Generator.h"

TileGrid *Generator::generate() {
  grid = new TileGrid();
  raiseTerrain();
  flattenTerrain();
  findZLimits();
  setTemperature();
  setLand();
  flattenContinentBorders();
  setTerrainLevel();
  setMoisture();
  setTerrainFromTileset();
  return grid;
}

void Generator::raiseTerrain() {
  // общее количество клеток суши
  int land_budget = MAP_HEIGHT * MAP_WIDTH;
  // количество начальных точек континентов
  int size = Random::get().getInt(40, 60);
  // количество точек в континенте
  int continent_size = land_budget / size;
  for (int i = 0; i < size; i++) {
    // определение центрального гекса континента
    auto prev = Vector2u(
        Random::get().getInt(0, MAP_WIDTH - 1),
        Random::get().getInt(LAND_BORDER, MAP_HEIGHT - LAND_BORDER - 1)
    );
    // построение континента вокруг центрального гекса
    for (int j = 0; j < continent_size; j++) {
      Tile *neighbour = grid->getNeighbour(Random::get().getInt(0, 6), prev);
      if (neighbour != nullptr) {
        float factor = 1;
        // если выбранный сосед за границей суши, уменьшается вероятность поднятия суши там
        if (neighbour->pos.y < LAND_BORDER)
          factor = min(factor, (float) neighbour->pos.y / LAND_BORDER);
        if (neighbour->pos.y > MAP_HEIGHT - LAND_BORDER - 1)
          factor = min(factor, (float) (MAP_HEIGHT - 1 - neighbour->pos.y) / LAND_BORDER);
        if ((float) Random::get().getInt(10, 100) / 100.f < factor) {
          neighbour->increaseZ(1);
          if (neighbour->getZ() > 0) {
            j--;
          }
        }
        prev = neighbour->pos;
      } else {
        j--;
      }
    }
  }
}

// сглаживание суши, эрозия
void Generator::flattenTerrain() {
  for (uint16_t i = 0; i < MAP_WIDTH; i++)
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      Tile *tile = grid->getTile({i, j});
      for (uint8_t k = 0; k < 6; k++) {
        Tile *neighbour = grid->getNeighbour(k, {i, j});
        if (neighbour != nullptr)
          if (tile->getZ() - neighbour->getZ() > 3) {
            tile->increaseZ(-1);
            neighbour->increaseZ(1);
          }
      }
    }
}

void Generator::findZLimits() {
  // общая высота всех тайлов
  int terrain_mass = 0;
  for (uint16_t i = 0; i < MAP_WIDTH; i++)
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      Tile *tile = grid->getTile({i, j});
      if (tile->getZ() > grid->getMaxZ()) {
        grid->setMaxZ(tile->getZ());
      }
      if (tile->getZ() < grid->getMinZ()) {
        grid->setMinZ(tile->getZ());
      }
      terrain_mass += tile->getZ();
    }
  terrain_mass /= (MAP_HEIGHT * MAP_WIDTH);
  ocean_level = (float) terrain_mass * OCEAN_LEVEL;
}

void Generator::setTemperature() {
  PerlinNoise perlin_noise = PerlinNoise(Random::get().getSeed() * 2);
  for (uint16_t i = 0; i < MAP_WIDTH; i++)
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      Tile *tile = grid->getTile({i, j});
      float temperature = 1 - tile->getLatitude() / 90.f;
      temperature *= (perlin_noise.noise(
          0.01f * (float) i,
          0.01f * (float) j,
          MAP_WIDTH * 0.01f,
          MAP_HEIGHT * 0.01f, 4) + 1) / 2.f;
      temperature *= 1 - abs(ocean_level - (float) tile->getZ()) / (float) (grid->getMaxZ() - ocean_level);
      temperature = pow(temperature, 1.f / 3);
      tile->setTemperature(TEMPERATURE_MIN + temperature * (TEMPERATURE_MAX - TEMPERATURE_MIN));
    }
}

// установка суши по уровню океана
void Generator::setLand() {
  for (uint16_t i = 0; i < MAP_WIDTH; i++)
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      Tile *tile = grid->getTile({i, j});
      if (tile->getZ() > ocean_level) {
        tile->setType("GenLand");
      }
    }
}

// сглаживание границ континентов, удаление полосок тайлов
void Generator::flattenContinentBorders() {
  for (uint8_t z = 0; z < 4; z++) {
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
      for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
        Tile *tile = grid->getTile({i, j});
        if (tile->getType()->type_name == "GenWater" && countNeighboursWithType("GenWater", tile) <= 2) {
          deleteTilePaths("GenWater", "GenLand", tile);
        } else if (tile->getType()->type_name == "GenLand" &&
            countNeighboursWithType("GenLand", tile) <= 2) {
          deleteTilePaths("GenLand", "GenWater", tile);
        }
      }
  }
}

void Generator::setTerrainLevel() {
  for (uint16_t i = 0; i < MAP_WIDTH; i++)
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      Tile *tile = grid->getTile({i, j});
      float relative_elevation;
      if (tile->getType()->above_sea_level) {
        relative_elevation = (float) (tile->getZ() - ocean_level) / (float) (grid->getMaxZ() - ocean_level);
      } else {
        relative_elevation = (float) (ocean_level - tile->getZ()) / (float) (ocean_level - grid->getMinZ());
      }
      if (relative_elevation > 0.35) {
        tile->setLevel(Level::HIGH);
      } else if (relative_elevation > 0.2) {
        tile->setLevel(Level::MEDIUM);
      } else if (relative_elevation > 0.05) {
        tile->setLevel(Level::SMALL);
      } else {
        tile->setLevel(Level::NO);
      }
    }
}

void Generator::setMoisture() {
  PerlinNoise perlin_noise = PerlinNoise(Random::get().getSeed());
  float max_moisture = 0;
  for (uint16_t i = 0; i < MAP_WIDTH; i++)
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      Tile *tile = grid->getTile({i, j});
      float moisture = 1 - tile->getLatitude() / 90.f;
      moisture *= (perlin_noise.noise(
          0.01f * (float) i,
          0.01f * (float) j,
          MAP_WIDTH * 0.01f,
          MAP_HEIGHT * 0.01f, 4) + 1) / 2.f;
      tile->setMoisture(moisture);
      if (moisture > max_moisture) max_moisture = moisture;
    }
}

void Generator::setTerrainFromTileset() {
  for (uint16_t i = 0; i < Tileset::get().getSize(); i++) {
    Type *type = Tileset::get().getType(i);
    for (uint16_t j = 0; j < MAP_WIDTH; j++)
      for (uint16_t k = 0; k < MAP_HEIGHT; k++) {
        Tile *tile = grid->getTile({j, k});
        if (tile->getZ() > ocean_level == type->above_sea_level &&
            tile->getTemperature() >= type->temperature_range->first &&
            tile->getTemperature() <= type->temperature_range->second &&
            tile->getMoisture() >= type->moisture_range->first &&
            tile->getMoisture() <= type->moisture_range->second &&
            ((type->neighbour.empty()) || (countNeighboursWithType(type->neighbour, tile) > 0))) {
          tile->setType(type->type_name);
        }
      }
  }
}

void Generator::deleteTilePaths(const string &type, const string &change_to, Tile *tile) {
  tile->setType(change_to);
  if (Tileset::get().getType(change_to)->above_sea_level) tile->setZ(ocean_level + 1);
  else tile->setZ(ocean_level - 1);
  if (countNeighboursWithType(type, tile) <= 2)
    for (uint8_t i = 0; i < 6; i++) {
      Tile *neighbour = grid->getNeighbour(i, tile);
      if (neighbour != nullptr)
        if (neighbour->getType()->type_name == type)
          deleteTilePaths(type, change_to, neighbour);
    }
}

uint8_t Generator::countNeighboursWithType(const string &type, Tile *tile) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < 6; i++)
    if (grid->getNeighbour(i, tile) != nullptr)
      if (grid->getNeighbour(i, tile)->getType()->type_name == type)
        count++;
  return count;
}