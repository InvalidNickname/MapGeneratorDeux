#include "GUI.h"

void GUI::render(RenderWindow *window) {
    mapModeDefault->render(window);
    mapModeBiomes->render(window);
}

bool GUI::checkClick(int _x, int _y) {
    bool check = mapModeDefault->checkClicked(_x, _y);
    if (check) {
        //TODO изменение режима карты
    }
    check = mapModeBiomes->checkClicked(_x, _y);
    if (check) {
        //TODO изменение режима карты
    }
    return check;
}

GUI::GUI(int windowWidth, int windowHeight) : windowHeight(windowHeight), windowWidth(windowWidth) {
    mapModeDefault = new Button(
            windowWidth - 41 - 41,
            windowHeight - 200 - 31,
            41,
            31,
            AssetLoader::get().getTexture("map_mode_default_0"),
            AssetLoader::get().getTexture("map_mode_default_1"));
    mapModeBiomes = new Button(
            windowWidth - 41,
            windowHeight - 200 - 31,
            41,
            31,
            AssetLoader::get().getTexture("map_mode_biomes_0"),
            AssetLoader::get().getTexture("map_mode_biomes_1"));
}
