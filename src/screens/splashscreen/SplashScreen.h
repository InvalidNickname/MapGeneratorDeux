#pragma once

#include <screens/Screen.h>
#include <screens/map/objects/tiles/type/Tileset.h>
#include <screens/map/MapScreen.h>
#include <thread>

using namespace sf;

class SplashScreen : public Screen {

  private:
    std::thread loadingThread;

    void draw() override;

    void doAction() override;

    void load();

  public:
    explicit SplashScreen(RenderWindow *renderWindow);
};