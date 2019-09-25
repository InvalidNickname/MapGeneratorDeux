#pragma once

#include <screens/Screen.h>
#include <screens/map/objects/tiles/Tileset.h>
#include <screens/map/MapScreen.h>

using namespace sf;

class SplashScreen : public Screen {

  private:
    void draw() override;

    void doAction() override;

  public:
    explicit SplashScreen(RenderWindow *renderWindow) : Screen(renderWindow) {};
};