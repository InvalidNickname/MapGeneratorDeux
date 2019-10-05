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
        int prevY = Random::get().getInt(LAND_BORDER, MAP_HEIGHT - LAND_BORDER - 1);
        // чтобы в каждой части карты было по центральной точке - убирает огромные океаны и континенты, дробит карту
        int prevX = Random::get().getInt(0, MAP_WIDTH - 1);
        // построение континента вокруг центрального гекса
        for (int j = 0; j < continentSize; j++) {
            Tile *neighbour = grid->getNeighbour(Random::get().getInt(0, 6), prevX, prevY);
            if (neighbour != nullptr) {
                double factor = 1;
                // если выбранный сосед за границей суши, уменьшается вероятность поднятия суши там
                if (neighbour->getY() < LAND_BORDER)
                    factor = min(factor, (double) neighbour->getY() / LAND_BORDER);
                if (neighbour->getY() > MAP_HEIGHT - LAND_BORDER - 1)
                    factor = min(factor, (double) (MAP_HEIGHT - 1 - neighbour->getY()) / LAND_BORDER);
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
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            for (int k = 0; k < 6; k++) {
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
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++) {
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
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++)
            grid->getTile(i, j)->setTemperature(oceanLevel, grid->getMaxZ());
}

// установка суши по уровню океана
void Generator::setLand() {
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            if (tile->getZ() >= oceanLevel) {
                tile->setType("GenLand");
            }
        }
}

// сглаживание границ континентов, удаление полосок тайлов
void Generator::flattenContinentBorders() {
    for (int z = 0; z < 4; z++) {
        for (int i = 0; i < MAP_WIDTH; i++)
            for (int j = 0; j < MAP_HEIGHT; j++) {
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
    for (int i = 0; i < MAP_WIDTH; i++)
        for (int j = 0; j < MAP_HEIGHT; j++) {
            Tile *tile = grid->getTile(i, j);
            double relativeElevation;
            if (tile->getType()->isAboveSeaLevel()) {
                relativeElevation = (double) (tile->getZ() - oceanLevel) / (grid->getMaxZ() - oceanLevel);
            } else {
                relativeElevation = (double) (oceanLevel - tile->getZ()) / (oceanLevel - grid->getMinZ());
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

void Generator::setTerrainFromTileset() {
    // TODO установка типов тайлов в соответствии с тайлсетом
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            Tile *tile = grid->getTile(j, i);
            if (tile->getType()->getTypeName() == "GenLand") {
                tile->setType("Plains");
            } else if (tile->getType()->getTypeName() == "GenWater") {
                tile->setType("Ocean");
            }
        }
}

void Generator::deleteTilePaths(const String &type, const String &changeTo, Tile *tile) {
    tile->setType(changeTo);
    if (countNeighboursWithType(type, tile) <= 2)
        for (int i = 0; i < 6; i++) {
            Tile *neighbour = grid->getNeighbour(i, tile);
            if (neighbour != nullptr)
                if (neighbour->getType()->getTypeName() == type)
                    deleteTilePaths(type, changeTo, neighbour);
        }
}

int Generator::countNeighboursWithType(const String &type, Tile *tile) {
    int count = 0;
    for (int i = 0; i < 6; i++)
        if (grid->getNeighbour(i, tile) != nullptr)
            if (grid->getNeighbour(i, tile)->getType()->getTypeName() == type)
                count++;
    return count;
}