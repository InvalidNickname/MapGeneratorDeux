add_library(generator src/Generator.cpp src/Generator.h src/utils/G.h src/utils/MapMode.h src/utils/PerlinNoise.h
        src/utils/PerlinNoise.cpp src/utils/Random.h src/tile/TileGrid.cpp src/tile/TileGrid.h src/tile/Tile.h
        src/tile/Tile.cpp src/tile/type/Level.h src/tile/type/Tileset.cpp src/tile/type/Tileset.h
        src/tile/type/Type.h src/tile/type/Type.cpp)

target_link_libraries(generator sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)

target_include_directories(generator PUBLIC src)
target_include_directories(generator PUBLIC ../libs/nlohmann)