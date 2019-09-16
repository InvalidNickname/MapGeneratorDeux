cmake_minimum_required(VERSION 3.14)
project(MapGeneratorDeux)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES src/main.cpp src/main.h src/screens/ScreenManager.cpp src/screens/ScreenManager.h src/screens/splashscreen/SplashScreen.cpp src/screens/splashscreen/SplashScreen.h src/screens/Screen.cpp src/screens/Screen.h src/screens/map/MapScreen.cpp src/screens/map/MapScreen.h)
set(SFML_DIR "libs/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML COMPONENTS system window graphics network audio main REQUIRED)

add_executable(MapGeneratorDeux ${SOURCE_FILES})

target_link_libraries(MapGeneratorDeux sfml-system sfml-window sfml-graphics sfml-network sfml-audio sfml-main)