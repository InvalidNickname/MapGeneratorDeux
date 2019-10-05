#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"

using namespace sf;

class ScreenManager {

  public:
    explicit ScreenManager(int initialKey, unsigned length);

    void addScreen(int _key, Screen *screen);

    void doActiveScreenActions();

    void drawActiveScreen();

  private:
    int key, tempKey{0}, prevKey{-1};
    std::vector<Screen *> screens;

};