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
#include "utils/G.h"

using Json = nlohmann::json;

class SettingsScreen : public Screen {

  using Screen::Screen;

 private:
  Vector2u window_size;
  GUI *gui;
  View ui_view;
  map<string, int16_t> settings;

  void prepare() override;

  void loadPrevSettings();

  bool getFromJSON(ifstream input);

  void setGUI();

  void writeSettings();

  GameState doAction() override;

  void handleInput();

  void draw() override;
};