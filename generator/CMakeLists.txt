add_library(generator src/generator.cpp src/generator.h src/utils/g.h src/utils/perlin_noise.h
        src/utils/perlin_noise.cpp src/utils/random.h src/tile/tile_grid.cpp src/tile/tile_grid.h src/tile/tile.h
        src/tile/tile.cpp src/tile/type/level.h src/tile/type/tileset.cpp src/tile/type/tileset.h
        src/tile/type/type.h src/tile/type/type.cpp)

target_link_libraries(generator sfml-system sfml-main)

target_include_directories(generator PUBLIC src)
target_include_directories(generator PUBLIC ../libs/nlohmann)