#include "Minimap.h"

Minimap::Minimap(uint16_t ww, uint16_t wh, DrawableGrid *dg) : window_height(wh), window_width(ww) {
  MINIMAP_X = (float) ww - MINIMAP_W;
  MINIMAP_Y = (float) wh - MINIMAP_H;

  createMinimapImage(dg);

  minimap.setTexture(minimap_texture->getTexture());
  minimap.setScale(300.f / minimap_texture->getTexture().getSize().x,
                   190.f / minimap_texture->getTexture().getSize().y);
  minimap.setPosition((float) ww - 300, (float) wh - 190);

  createViewRectangles();
}

void Minimap::render(RenderWindow *window) {
  window->draw(minimap);
  if (center.getSize() != Vector2f(0, 0)) {
    window->draw(center);
  } else {
    window->draw(left);
    window->draw(right);
  }
}

void Minimap::updateViewRegion(Vector2s lowerLeft, Vector2s upperRight) {
  if (lowerLeft.x >= 0 && upperRight.x < MAP_WIDTH) {
    center.setSize(Vector2f(MINIMAP_W * (float) (upperRight.x - lowerLeft.x) / MAP_WIDTH,
                            MINIMAP_H * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT));
    center.setPosition(MINIMAP_X + MINIMAP_W * (float) lowerLeft.x / MAP_WIDTH,
                       MINIMAP_Y + MINIMAP_H * (float) lowerLeft.y / MAP_HEIGHT);
  } else {
    // обнуление размеров чтобы не отрисовывать
    center.setSize({0, 0});

    if (lowerLeft.x < 0) lowerLeft.x = MAP_WIDTH + lowerLeft.x;
    if (upperRight.x >= MAP_WIDTH) upperRight.x = upperRight.x % MAP_WIDTH;

    right.setSize(Vector2f(MINIMAP_W * (float) (MAP_WIDTH - lowerLeft.x) / MAP_WIDTH,
                           MINIMAP_H * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT));
    right.setPosition(MINIMAP_X + MINIMAP_W * (float) lowerLeft.x / MAP_WIDTH,
                      MINIMAP_Y + MINIMAP_H * (float) lowerLeft.y / MAP_HEIGHT);

    left.setSize(Vector2f(MINIMAP_W * (float) (upperRight.x) / MAP_WIDTH,
                          MINIMAP_H * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT));
    left.setPosition(MINIMAP_X,
                     MINIMAP_Y + MINIMAP_H * (float) lowerLeft.y / MAP_HEIGHT);
  }
}

void Minimap::createMinimapImage(DrawableGrid *drawable_grid) {
  float height = 0.25f * TILE_HEIGHT * (3 * MAP_HEIGHT);
  float width = TILE_WIDTH * (0.5f + MAP_WIDTH);
  float camX = width / 2;
  float camY = 0.125f * TILE_HEIGHT * (3 * MAP_HEIGHT);

  View view;
  view.setCenter(camX, camY);
  view.setSize(width, height);

  minimap_texture = new RenderTexture();
  minimap_texture->create(window_width, window_height);
  minimap_texture->setView(view);

  Sprite background;
  background.setTexture(*AssetLoader::get().getTexture("minimap_background"));
  background.setScale(width / background.getTexture()->getSize().x, height / background.getTexture()->getSize().y);

  Sprite overlay;
  overlay.setTexture(*AssetLoader::get().getTexture("minimap_overlay"));
  overlay.setScale(width / overlay.getTexture()->getSize().x, height / overlay.getTexture()->getSize().y);
  overlay.setColor(Color(255, 255, 255, 150));

  minimap_texture->draw(background);
  drawable_grid->renderTexture(minimap_texture, MapMode::MINIMAP, 0, MAP_WIDTH);
  minimap_texture->draw(overlay);
  minimap_texture->display();
}

void Minimap::createViewRectangles() {
  center.setOutlineThickness(-2);
  center.setOutlineColor(Color(255, 255, 255, 150));
  center.setFillColor(Color::Transparent);

  left.setOutlineThickness(-2);
  left.setOutlineColor(Color(255, 255, 255, 150));
  left.setFillColor(Color::Transparent);

  right.setOutlineThickness(-2);
  right.setOutlineColor(Color(255, 255, 255, 150));
  right.setFillColor(Color::Transparent);
}
