#include "Generator.h"

Generator::Generator(int seed) {
    engine = default_random_engine{static_cast<long unsigned int>(seed)};
}

TileGrid *Generator::generate() {
    grid = new TileGrid();
    // общее количество клеток суши
    int landBudget = MAP_HEIGHT * MAP_WIDTH;
    // количество начальных точек континентов
    int size = random(40, 60);
    // точек в континенте
    continentSize = landBudget / size;
    raiseTerrain(size);
    findOceanLevel();
    flattenTerrain();
    setTerrainTypes();
    findZLimits();
    setTerrainElevation();
    return grid;
}

void Generator::findOceanLevel() {
    long tileHeight = 0;
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++)
            tileHeight += grid->getTile(j, i)->getZ();
    oceanLevel = (int) (tileHeight / (MAP_HEIGHT * MAP_WIDTH) * 1.2f);
}

void Generator::setTerrainElevation() {
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            Tile *tile = grid->getTile(j, i);
            if (tile->getType()->isAboveSeaLevel()) {
                double relativeElevation = (double) (tile->getZ() - oceanLevel) / (oceanLevel);
                if (relativeElevation > 0.7) {
                    tile->setLevel(Level::HIGH);
                } else if (relativeElevation > 0.5) {
                    tile->setLevel(Level::MEDIUM);
                } else if (relativeElevation > 0.3) {
                    tile->setLevel(Level::SMALL);
                } else {
                    tile->setLevel(Level::NO);
                }
            } else {
                double relativeElevation = (double) (oceanLevel - tile->getZ()) / (oceanLevel);
                if (relativeElevation > 0.7) {
                    tile->setLevel(Level::HIGH);
                } else if (relativeElevation > 0.5) {
                    tile->setLevel(Level::MEDIUM);
                } else if (relativeElevation > 0.3) {
                    tile->setLevel(Level::SMALL);
                } else {
                    tile->setLevel(Level::NO);
                }
            }
        }
}

void Generator::flattenTerrain() {
    // эрозия
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            Tile *tile = grid->getTile(j, i);
            for (int k = 0; k < 6; k++) {
                Tile *neighbour = grid->getNeighbour(k, j, i);
                if (neighbour != nullptr)
                    if (tile->getZ() - neighbour->getZ() > 3) {
                        tile->increaseZ(-1);
                        neighbour->increaseZ(1);
                    }
            }
        }
}

void Generator::flattenContinentBorders() {
    for (int z = 0; z < 4; z++) {
        for (int i = 0; i < MAP_HEIGHT; i++)
            for (int j = 0; j < MAP_WIDTH; j++)
                if (grid->getTile(j, i)->getType()->getArchtype() == "Water" &&
                    tileSurroundedByArchtype("Water", grid->getTile(j, i)) <= 2) {
                    deleteTilePaths("Ocean", "Plains", grid->getTile(j, i));
                } else if (grid->getTile(j, i)->getType()->getArchtype() == "Plains" &&
                           tileSurroundedByArchtype("Plains", grid->getTile(j, i)) <= 2) {
                    deleteTilePaths("Plains", "Ocean", grid->getTile(j, i));
                }
    }
}

void Generator::setTerrainTypes() {
    // установка суши по уровню океана
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            Tile *tile = grid->getTile(j, i);
            if (tile->getZ() >= oceanLevel) {
                tile->setType("Plains");
            }
        }
    flattenContinentBorders();
}

void Generator::deleteTilePaths(const String &type, const String &changeTo, Tile *tile) {
    grid->getTile(tile->getX(), tile->getY())->setType(changeTo);
    if (tileSurroundedByType(type, tile) == 2)
        for (int i = 0; i < 6; i++) {
            Tile *neighbour = grid->getNeighbour(i, tile->getX(), tile->getY());
            if (neighbour != nullptr)
                if (neighbour->getType()->getTypeName() == type)
                    deleteTilePaths(type, changeTo, neighbour);
        }
}

void Generator::findZLimits() {
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            Tile *tile = grid->getTile(j, i);
            if (tile->getZ() > grid->getMaxZ()) {
                grid->setMaxZ(tile->getZ());
                maxZ = tile->getZ();
            }
        }
    minZ = maxZ;
    for (int i = 0; i < MAP_HEIGHT; i++)
        for (int j = 0; j < MAP_WIDTH; j++) {
            Tile *tile = grid->getTile(j, i);
            if (tile->getZ() < minZ) {
                grid->setMinZ(tile->getZ());
                minZ = tile->getZ();
            }
        }
}

int Generator::tileSurroundedByType(const String &type, Tile *tile) {
    int count = 0;
    for (int i = 0; i < 6; i++)
        if (grid->getNeighbour(i, tile->getX(), tile->getY()) != nullptr)
            if (grid->getNeighbour(i, tile->getX(), tile->getY())->getType()->getTypeName() == type)
                count++;
    return count;
}

int Generator::tileSurroundedByArchtype(const String &archtype, Tile *tile) {
    int count = 0;
    for (int i = 0; i < 6; i++)
        if (grid->getNeighbour(i, tile->getX(), tile->getY()) != nullptr)
            if (grid->getNeighbour(i, tile->getX(), tile->getY())->getType()->getArchtype() == archtype)
                count++;
    return count;
}

void Generator::raiseTerrain(int size) {
    for (int i = 0; i < size; i++) {
        // определение центрального гекса континента
        int prevY = random(LAND_BORDER, MAP_HEIGHT - LAND_BORDER - 1);
        // чтобы в каждой части карты было по центральной точке - убирает огромные океаны
        int prevX = random(0, MAP_WIDTH - 1);
        // построение континента вокруг центрального гекса
        for (int j = 0; j < continentSize; j++) {
            int destination = random(0, 6);
            Tile *neighbour = grid->getNeighbour(destination, prevX, prevY);
            if (neighbour != nullptr) {
                double factor = 1;
                if (neighbour->getY() < LAND_BORDER)
                    factor = min(factor, (double) neighbour->getY() / LAND_BORDER);
                if (neighbour->getY() > MAP_HEIGHT - LAND_BORDER - 1)
                    factor = min(factor, (double) (MAP_HEIGHT - 1 - neighbour->getY()) / LAND_BORDER);
                if ((float) random(10, 100) / 100.f < factor) {
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

int Generator::random(int x, int y) {
    uniform_int_distribution<int> distribution(x, y);
    return distribution(engine);
}