#include "ScreenManager.h"

ScreenManager::ScreenManager(int initial_key, uint32_t length) : key(initial_key) {
  screens.reserve(length);
}

void ScreenManager::addScreen(int _key, Screen *screen) {
  screens[_key] = screen;
}

void ScreenManager::doActiveScreenActions() {
  if (key >= 0) {
    // если это новый экран - подготовить
    if (key != prev_key) {
      screens[key]->prepare();
      prev_key = key;
    }
    temp_key = screens[key]->doAction();
    if (temp_key != THIS_STATE) {
      key = temp_key;
    }
  }
}

void ScreenManager::drawActiveScreen() {
  // если этот экран подоготовлен - отрисовка
  if (key >= 0 && key == prev_key) {
    screens[key]->draw();
  }
}