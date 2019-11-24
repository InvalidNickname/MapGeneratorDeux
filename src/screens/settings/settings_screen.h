#ifndef MGD_SRC_SCREENS_SETTINGS_SETTINGS_SCREEN_H
#define MGD_SRC_SCREENS_SETTINGS_SETTINGS_SCREEN_H

#include <iomanip>
#include <string>
#include <map>
#include <fstream> // для считывания json-файла

#include <json.hpp>

#include <gui.h>
#include <radio_buttons.h>
#include <drawable_image.h>
#include <drawable_text.h>
#include <utils/random.h>
#include <utils/g.h>

#include "screens/screen.h"
#include "utils/r.h"
#include "utils/asset_loader.h"

using Json = nlohmann::json;

class SettingsScreen : public Screen {

  using Screen::Screen;

 private:
  Vector2u window_size_;
  GUI *gui_;
  View ui_;
  map<string, string> settings_;
  uint32_t seed;

  void Prepare() override;

  void LoadPrevSettings();

  bool GetFromJSON(ifstream input);

  void SetGUI();

  void WriteSettings();

  GameState DoAction() override;

  void HandleInput();

  void Draw() override;
};

#endif