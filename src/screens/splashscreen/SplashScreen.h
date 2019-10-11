#pragma once

#include <thread>
#include <future>
#include <chrono>

#include <screens/Screen.h>
#include <screens/map/objects/tiles/type/Tileset.h>
#include <screens/map/MapScreen.h>

#include "utils/AssetLoader.h"

using namespace sf;

class SplashScreen : public Screen {

  using Screen::Screen;

 private:
  std::future<void> loadingThread;

  void prepare() override;

  void load();

  int doAction() override;

  void draw() override;
};