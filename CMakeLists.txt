cmake_minimum_required(VERSION 3.14)
project(MapGeneratorDeux)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp src/screens/ScreenManager.cpp src/screens/splashscreen/SplashScreen.cpp
        src/screens/map/MapScreen.cpp src/screens/map/objects/tiles/type/Tileset.cpp src/screens/map/objects/tiles/Tile.cpp
        src/screens/map/objects/tiles/type/Type.cpp src/screens/map/objects/DrawableGrid.cpp
        src/screens/map/objects/tiles/TileGrid.cpp src/screens/map/Generator.cpp)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS system window graphics network audio main REQUIRED)

add_executable(MapGeneratorDeux ${SOURCE_FILES})
include_directories(src)
include_directories(libs/nlohmann)

target_link_libraries(MapGeneratorDeux sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)