#pragma once

#include <iomanip>
#include <string>
#include <map>
#include <fstream> // для считывания json-файла

#include <json.hpp>

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
  map<string, int> settings;

  void prepare() override;

  void loadPrevSettings();

  bool getFromJSON(ifstream input);

  void setGUI();

  void writeSettings();

  GameState doAction() override;

  void handleInput();

  void draw() override;
};