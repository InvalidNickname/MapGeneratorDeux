cmake_minimum_required(VERSION 3.14)
project(MapGeneratorDeux)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML COMPONENTS system window graphics network audio main REQUIRED)

set(SOURCE_FILES src/main.cpp src/screens/screen_manager.cpp src/screens/splashscreen/splash_screen.cpp
        src/screens/map/map_screen.cpp src/screens/map/drawables/drawable_grid.cpp
        src/utils/asset_loader.cpp src/screens/map/drawables/minimap.cpp src/utils/r.h
        src/screens/settings/settings_screen.cpp
        src/screens/map/map_mode.h)
add_executable(MapGeneratorDeux WIN32 ${SOURCE_FILES})

add_subdirectory(generator)
add_subdirectory(ui)

target_include_directories(MapGeneratorDeux PUBLIC src)
target_include_directories(MapGeneratorDeux PUBLIC libs/nlohmann)

target_link_libraries(MapGeneratorDeux sfml-system sfml-graphics sfml-main)
target_link_libraries(MapGeneratorDeux generator ui)

add_custom_command(TARGET MapGeneratorDeux POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libs/SFML-2.5.1/bin"
        $<TARGET_FILE_DIR:MapGeneratorDeux>)

install(TARGETS MapGeneratorDeux
        RUNTIME DESTINATION build
        LIBRARY DESTINATION build)
install(DIRECTORY assets/ DESTINATION build PATTERN "last_settings.json" EXCLUDE)
install(DIRECTORY libs/SFML-2.5.1/bin/ DESTINATION build)