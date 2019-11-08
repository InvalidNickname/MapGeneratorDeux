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
  Vector2u window_size;
  GUI *gui;
  View ui_view;
  GameState temp_key{THIS_STATE};

  void prepare() override;

  void setGUI();

  GameState doAction() override;

  void handleInput();

  void draw() override;
};