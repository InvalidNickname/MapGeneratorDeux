#pragma once

#include <future>
#include <chrono>

#include "screens/Screen.h"
#include "screens/map/objects/tiles/type/Tileset.h"
#include "utils/AssetLoader.h"
#include "utils/R.h"

class SplashScreen : public Screen {

  using Screen::Screen;

 private:
  std::future<void> loading_thread;

  void prepare() override;

  void load();

  GameState doAction() override;

  void draw() override;
};