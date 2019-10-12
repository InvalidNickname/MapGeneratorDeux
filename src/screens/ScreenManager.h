#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"

using namespace sf;

class ScreenManager {

 public:
  explicit ScreenManager(int initial_key, uint32_t length);

  void addScreen(int _key, Screen *screen);

  void doActiveScreenActions();

  void drawActiveScreen();

 private:
  int key, temp_key{0}, prev_key{-1};
  std::vector<Screen *> screens;

};