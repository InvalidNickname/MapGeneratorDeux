#include "Minimap.h"

Minimap::Minimap(uint16_t ww, uint16_t wh, DrawableGrid *dg) : window_height(wh), window_width(ww) {
  pos_x = ww - R::get().getUint("minimap_width");
  pos_y = wh - R::get().getUint("minimap_height");

  createMinimapImage(dg);
  createViewRectangles();
}

void Minimap::render(RenderWindow *window) {
  window->draw(minimap);
  window->draw(right);
  if (left.getSize() != Vector2f(0, 0)) {
    window->draw(left);
  }
  window->draw(overlay);
}

void Minimap::updateViewRegion(Vector2s lowerLeft, Vector2s upperRight) {
  if (lowerLeft.x >= 0 && upperRight.x < MAP_WIDTH) {
    right.setSize(
        {(float) R::get().getUint("minimap_width") * (float) (upperRight.x - lowerLeft.x) / MAP_WIDTH,
         (float) R::get().getUint("minimap_height") * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT}
    );
    right.setPosition(
        {(float) pos_x + (float) R::get().getUint("minimap_width") * (float) lowerLeft.x / MAP_WIDTH,
         (float) pos_y + (float) R::get().getUint("minimap_height") * (float) lowerLeft.y / MAP_HEIGHT}
    );

    left.setSize({0, 0});
  } else {
    if (lowerLeft.x < 0) lowerLeft.x = MAP_WIDTH + lowerLeft.x;
    if (upperRight.x >= MAP_WIDTH) upperRight.x = upperRight.x % MAP_WIDTH;

    right.setSize(
        {(float) R::get().getUint("minimap_width") * (float) (MAP_WIDTH - lowerLeft.x) / MAP_WIDTH,
         (float) R::get().getUint("minimap_height") * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT}
    );
    right.setPosition(
        {(float) pos_x + (float) R::get().getUint("minimap_width") * (float) lowerLeft.x / MAP_WIDTH,
         (float) pos_y + (float) R::get().getUint("minimap_height") * (float) lowerLeft.y / MAP_HEIGHT}
    );

    left.setSize(
        {(float) R::get().getUint("minimap_width") * (float) (upperRight.x) / MAP_WIDTH,
         (float) R::get().getUint("minimap_height") * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT}
    );
    left.setPosition(
        {(float) pos_x,
         (float) pos_y + (float) R::get().getUint("minimap_height") * (float) lowerLeft.y / MAP_HEIGHT}
    );
  }
}

void Minimap::createMinimapImage(DrawableGrid *drawable_grid) {
  // отрисованная карта
  auto minimap_texture = new RenderTexture();
  minimap_texture->create(window_width, window_height);
  minimap_texture->setView(View(
      {TILE_WIDTH * (0.5f + MAP_WIDTH) / 2, 0.125f * TILE_HEIGHT * (3 * MAP_HEIGHT)},
      {TILE_WIDTH * (0.5f + MAP_WIDTH), 0.25f * TILE_HEIGHT * (3 * MAP_HEIGHT)}
  ));
  drawable_grid->renderTexture(minimap_texture, MapMode::MINIMAP, 0, MAP_WIDTH);
  minimap_texture->display();

  minimap.setTexture(minimap_texture->getTexture());
  minimap.setScale(
      {(float) R::get().getUint("minimap_width") / minimap_texture->getTexture().getSize().x,
       (float) R::get().getUint("minimap_height") / minimap_texture->getTexture().getSize().y}
  );
  minimap.setPosition(pos_x, pos_y);

  overlay.setTexture(*AssetLoader::get().getTexture("minimap_overlay"));
  overlay.setScale(
      {(float) R::get().getUint("minimap_width") / overlay.getTexture()->getSize().x,
       (float) R::get().getUint("minimap_height") / overlay.getTexture()->getSize().y}
  );
  overlay.setPosition(pos_x, pos_y);
}

void Minimap::createViewRectangles() {
  left.setOutlineThickness(-2);
  left.setOutlineColor(Color::White);
  left.setFillColor(Color::Transparent);

  right.setOutlineThickness(-2);
  right.setOutlineColor(Color::White);
  right.setFillColor(Color::Transparent);
}
