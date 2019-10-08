#pragma once

#include <ui/UIDrawable.h>

#include <utils/AssetLoader.h>
#include <utils/GenerationParameters.h>

#include "DrawableGrid.h"

using namespace sf;

class Minimap : public UIDrawable {
  public:
    Minimap(uint16_t windowWidth, uint16_t windowHeight, DrawableGrid *drawableGrid);

    void render(RenderWindow *window) override;

    bool isClickable() override { return false; };

    bool checkClicked(Vector2i coords) override { return false; };

  private:
    RenderTexture *minimapTexture;
    Sprite minimap;

};
