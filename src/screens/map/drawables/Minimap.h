#pragma once

#include <ui/UIDrawable.h>

#include <utils/AssetLoader.h>
#include <utils/GenerationParameters.h>

#include "DrawableGrid.h"

using namespace sf;

class Minimap : public UIDrawable {
  public:
    Minimap(float windowWidth, float windowHeight, DrawableGrid *drawableGrid);

    void render(RenderWindow *window) override;

    bool isClickable() override { return false; };

    bool checkClicked(float _x, float _y) override { return false; };

  private:
    RenderTexture *minimapTexture;
    Sprite minimap;

};
