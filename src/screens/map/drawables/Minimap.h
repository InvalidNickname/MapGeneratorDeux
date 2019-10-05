#pragma once

#include <ui/UIDrawable.h>

#include <screens/splashscreen/AssetLoader.h>
#include <screens/map/generator/GenerationParameters.h>

#include "DrawableGrid.h"

using namespace sf;

class Minimap : public UIDrawable {
  public:
    Minimap(float windowWidth, float windowHeight, float minZoom, DrawableGrid *drawableGrid);

    void render(RenderWindow *window) override;

    bool isClickable() override { return false; };

    bool checkClicked(float _x, float _y) override { return false; };

  private:
    Sprite minimapBackground;
    RenderTexture *minimapTexture;
    Sprite minimap;

};
