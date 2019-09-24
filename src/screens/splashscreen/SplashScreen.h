#pragma once

#include "../Screen.h"
#include "../map/objects/tiles/Tileset.h"

class SplashScreen : public Screen {

  private:
    void draw() override;

  public:
    explicit SplashScreen(RenderWindow *renderWindow) : Screen(renderWindow) {};
};