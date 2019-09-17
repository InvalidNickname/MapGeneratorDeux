#include "ScreenManager.h"

void ScreenManager::drawActiveScreen() {
    activeScreen->draw();
}

void ScreenManager::setActiveScreen(Screen *screen) {
    activeScreen = screen;
}

ScreenManager::ScreenManager(Screen *activeScreen) : activeScreen(activeScreen) {}