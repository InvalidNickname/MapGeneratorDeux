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
    int landBudget = MAP_HEIGHT * MAP_WIDTH;
    // количество начальных точек континентов
    int size = Random::get().getInt(40, 60);
    // количество точек в континенте
    int continentSize = landBudget / size;
    for (int i = 0; i < size; i++) {
        // определение центрального гекса континента
        uint16_t prevY = Random::get().getInt(LAND_BORDER, MAP_HEIGHT - LAND_BORDER - 1);
        // чтобы в каждой части карты было по центральной точке - убирает огромные океаны и континенты, дробит карту
        uint16_t prevX = Random::get().getInt(0, MAP_WIDTH - 1);
        // построение континента вокруг центрального гекса
        for (int j = 0; j < continentSize; j++) {
            Tile *neighbour = grid->getNeighbour(Random::get().getInt(0, 6), prevX, prevY);
            if (neighbour != nullptr) {
                float factor = 1;
                // если выбранный сосед за границей суши, уменьшается вероятность поднятия суши там
                if (neighbour->getY() < LAND_BORDER)
                    factor = min(factor, (float) neighbour->getY() / LAND_BORDER);
                if (neighbour->getY() > MAP_HEIGHT - LAND_BORDER - 1)
                    factor = min(factor, (float) (MAP_HEIGHT - 1 - neighbour->getY()) / LAND_BORDER);
                if ((float) Random::get().getInt(10, 100) / 100.f < factor) {
                    neighbour->increaseZ(1);
                    if (neighbour->getZ() > 0) {
                        j--;
                    }
                }
                prevX = neighbour->getX();
                prevY = neighbour->getY();
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
            Tile *tile = grid->getTile(i, j);
            for (uint8_t k = 0; k < 6; k++) {
                Tile *neighbour = grid->getNeighbour(k, i, j);
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
    int terrainMass = 0;
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            if (tile->getZ() > grid->getMaxZ()) {
                grid->setMaxZ(tile->getZ());
            }
            if (tile->getZ() < grid->getMinZ()) {
                grid->setMinZ(tile->getZ());
            }
            terrainMass += tile->getZ();
        }
    terrainMass /= (MAP_HEIGHT * MAP_WIDTH);
    oceanLevel = (int) ((float) terrainMass * OCEAN_LEVEL);
}

void Generator::setTemperature() {
    PerlinNoise perlinNoise = PerlinNoise(Random::get().getSeed() * 2);
    int16_t maxTemperature = 0;
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            float temperature = (1 - tile->getLatitude() / 90.f) * 20.f;
            temperature = temperature * perlinNoise.noise(0.015f * (float) i, 0.015f * (float) j, 0.5f);
            temperature *= 1 - pow(abs(
                    (float) oceanLevel - (float) tile->getZ()) / (float) (grid->getMaxZ() - oceanLevel), 2);
            temperature = TEMPERATURE_MIN + temperature * (TEMPERATURE_MAX - TEMPERATURE_MIN);
            tile->setTemperature(temperature);
            if (temperature > maxTemperature) maxTemperature = temperature;
        }
    // т.к. температура зависит от положения тайла и уменьшается к экватору, максимальная температура будет меньше 50
    // поэтому надо распределить получившуюся температуру от -10 до 50
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            if (tile->getTemperature() > 0)
                tile->setTemperature(TEMPERATURE_MAX * tile->getTemperature() / maxTemperature);
        }
}

// установка суши по уровню океана
void Generator::setLand() {
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            if (tile->getZ() > oceanLevel) {
                tile->setType("GenLand");
            }
        }
}

// сглаживание границ континентов, удаление полосок тайлов
void Generator::flattenContinentBorders() {
    for (uint8_t z = 0; z < 4; z++) {
        for (uint16_t i = 0; i < MAP_WIDTH; i++)
            for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
                Tile *tile = grid->getTile(i, j);
                if (tile->getType()->getTypeName() == "GenWater" && countNeighboursWithType("GenWater", tile) <= 2) {
                    deleteTilePaths("GenWater", "GenLand", tile);
                } else if (tile->getType()->getTypeName() == "GenLand" &&
                           countNeighboursWithType("GenLand", tile) <= 2) {
                    deleteTilePaths("GenLand", "GenWater", tile);
                }
            }
    }
}

void Generator::setTerrainLevel() {
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            float relativeElevation;
            if (tile->getType()->isAboveSeaLevel()) {
                relativeElevation = (float) (tile->getZ() - oceanLevel) / (float) (grid->getMaxZ() - oceanLevel);
            } else {
                relativeElevation = (float) (oceanLevel - tile->getZ()) / (float) (oceanLevel - grid->getMinZ());
            }
            if (relativeElevation > 0.35) {
                tile->setLevel(Level::HIGH);
            } else if (relativeElevation > 0.2) {
                tile->setLevel(Level::MEDIUM);
            } else if (relativeElevation > 0.05) {
                tile->setLevel(Level::SMALL);
            } else {
                tile->setLevel(Level::NO);
            }
        }
}

void Generator::setMoisture() {
    PerlinNoise perlinNoise = PerlinNoise(Random::get().getSeed());
    float maxMoisture = 0;
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            float moisture = 1 - tile->getLatitude() / 90.f;
            moisture = moisture * perlinNoise.noise(0.015f * (float) i, 0.015f * (float) j, 0.4f);
            tile->setMoisture(moisture);
            if (moisture > maxMoisture) maxMoisture = moisture;
        }
    // т.к. влажность зависит от положения тайла и уменьшается к экватору, максимальная влажность будет меньше 1
    // поэтому надо распределить получившуюся влажность от 0 до 1
    for (uint16_t i = 0; i < MAP_WIDTH; i++)
        for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            tile->setMoisture(tile->getMoisture() / maxMoisture);
        }
}

void Generator::setTerrainFromTileset() {
    for (uint16_t i = 0; i < Tileset::get().getSize(); i++) {
        Type *type = Tileset::get().getType(i);
        for (uint16_t j = 0; j < MAP_WIDTH; j++)
            for (uint16_t k = 0; k < MAP_HEIGHT; k++) {
                Tile *tile = grid->getTile(j, k);
                if (tile->getZ() > oceanLevel == type->isAboveSeaLevel() &&
                    tile->getTemperature() >= type->getTemperatureRange()->first &&
                    tile->getTemperature() <= type->getTemperatureRange()->second &&
                    tile->getMoisture() >= type->getMoistureRange()->first &&
                    tile->getMoisture() <= type->getMoistureRange()->second &&
                    ((type->getNeighbour().empty()) || (countNeighboursWithType(type->getNeighbour(), tile)))) {
                    tile->setType(type->getTypeName());
                }
            }
    }
}

void Generator::deleteTilePaths(const string &type, const string &changeTo, Tile *tile) {
    tile->setType(changeTo);
    if (Tileset::get().getType(changeTo)->isAboveSeaLevel()) tile->increaseZ(oceanLevel + 1 - tile->getZ());
    else tile->increaseZ(oceanLevel - 1 - tile->getZ());
    if (countNeighboursWithType(type, tile) <= 2)
        for (uint8_t i = 0; i < 6; i++) {
            Tile *neighbour = grid->getNeighbour(i, tile);
            if (neighbour != nullptr)
                if (neighbour->getType()->getTypeName() == type)
                    deleteTilePaths(type, changeTo, neighbour);
        }
}

uint8_t Generator::countNeighboursWithType(const string &type, Tile *tile) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < 6; i++)
        if (grid->getNeighbour(i, tile) != nullptr)
            if (grid->getNeighbour(i, tile)->getType()->getTypeName() == type)
                count++;
    return count;
}