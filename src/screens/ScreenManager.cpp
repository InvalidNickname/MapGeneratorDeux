#include "ScreenManager.h"

void ScreenManager::drawActiveScreen() {
    activeScreen->draw();
}

void ScreenManager::setActiveScreen(Screen *_screen) {
    activeScreen = _screen;
    activeScreen->setMoveFunction([this](Screen *screen) {
        setActiveScreen(screen);
    });
}

ScreenManager::ScreenManager(Screen *_screen) {
    setActiveScreen(_screen);
}

void ScreenManager::doActiveScreenActions() {
    activeScreen->doAction();
}
