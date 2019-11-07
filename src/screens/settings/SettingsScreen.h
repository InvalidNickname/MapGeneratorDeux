#pragma once

#include "ui/GUI.h"
#include "screens/Screen.h"
#include "ui/RadioButtons.h"
#include "utils/R.h"
#include "utils/AssetLoader.h"
#include "ui/DrawableImage.h"

class SettingsScreen : public Screen {

  using Screen::Screen;

 private:
  uint16_t window_width, window_height;
  GUI *gui;
  View ui_view;

  void prepare() override;

  void setGUI();

  GameState doAction() override;

  void handleInput();

  void draw() override;
};