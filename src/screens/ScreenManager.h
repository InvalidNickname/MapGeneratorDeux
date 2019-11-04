#pragma once

#include "Screen.h"

class ScreenManager {

 public:
  explicit ScreenManager(GameState initial_key, uint32_t length);

  void addScreen(GameState _key, Screen *screen);

  void doActiveScreenActions();

  void drawActiveScreen();

 private:
  GameState key, temp_key{SPLASHSCREEN}, prev_key{EXIT};
  std::vector<Screen *> screens;

};