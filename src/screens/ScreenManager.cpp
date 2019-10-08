#include "ScreenManager.h"

ScreenManager::ScreenManager(int initialKey, uint32_t length) : key(initialKey) {
    screens.reserve(length);
}

void ScreenManager::addScreen(int _key, Screen *screen) {
    screens[_key] = screen;
}

void ScreenManager::doActiveScreenActions() {
    if (key >= 0) {
        // если это новый экран - подготовить
        if (key != prevKey) {
            screens[key]->prepare();
            prevKey = key;
        }
        tempKey = screens[key]->doAction();
        if (tempKey != THIS_STATE) {
            key = tempKey;
        }
    }
}

void ScreenManager::drawActiveScreen() {
    // если этот экран подоготовлен - отрисовка
    if (key >= 0 && key == prevKey) {
        screens[key]->draw();
    }
}