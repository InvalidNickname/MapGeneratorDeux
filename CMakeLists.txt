cmake_minimum_required(VERSION 3.14)
project(MapGeneratorDeux)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML COMPONENTS system window graphics network audio main REQUIRED)

set(SOURCE_FILES src/main.cpp src/screens/ScreenManager.cpp src/screens/splashscreen/SplashScreen.cpp
        src/screens/map/MapScreen.cpp src/screens/map/objects/tiles/type/Tileset.cpp src/screens/map/objects/tiles/Tile.cpp
        src/screens/map/objects/tiles/type/Type.cpp src/screens/map/drawables/DrawableGrid.cpp
        src/screens/map/objects/tiles/TileGrid.cpp src/screens/map/generator/Generator.cpp
        src/ui/GUI.cpp src/ui/Button.cpp src/utils/AssetLoader.cpp src/ui/RadioButtons.cpp
        src/screens/map/drawables/Minimap.cpp src/utils/PerlinNoise.cpp src/utils/R.h src/utils/R.cpp
        src/screens/map/drawables/TileInfoList.cpp)
add_executable(MapGeneratorDeux ${SOURCE_FILES})

target_include_directories(MapGeneratorDeux PUBLIC src)
target_include_directories(MapGeneratorDeux PUBLIC libs/nlohmann)

target_link_libraries(MapGeneratorDeux sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)

add_custom_command(TARGET MapGeneratorDeux POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libs/SFML-2.5.1/bin"
        $<TARGET_FILE_DIR:MapGeneratorDeux>)

install(TARGETS MapGeneratorDeux
        RUNTIME DESTINATION build
        LIBRARY DESTINATION build)
install(DIRECTORY assets/ libs/SFML-2.5.1/bin/ DESTINATION build)