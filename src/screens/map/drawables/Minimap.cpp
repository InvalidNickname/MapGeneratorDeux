#include "Minimap.h"

Minimap::Minimap(Vector2u window_size, DrawableGrid *dg) : window_size(window_size) {
  pos.x = window_size.x - R::minimap_width;
  pos.y = window_size.y - R::minimap_height;

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
        {R::minimap_width * (float) (upperRight.x - lowerLeft.x) / MAP_WIDTH,
         R::minimap_height * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT}
    );
    right.setPosition(
        {pos.x + R::minimap_width * (float) lowerLeft.x / MAP_WIDTH,
         pos.y + R::minimap_height * (float) lowerLeft.y / MAP_HEIGHT}
    );
    left.setSize({0, 0});
  } else {
    if (lowerLeft.x < 0) lowerLeft.x += MAP_WIDTH;
    if (upperRight.x >= MAP_WIDTH) upperRight.x %= MAP_WIDTH;

    right.setSize(
        {R::minimap_width * (float) (MAP_WIDTH - lowerLeft.x) / MAP_WIDTH,
         R::minimap_height * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT}
    );
    right.setPosition(
        {pos.x + R::minimap_width * (float) lowerLeft.x / MAP_WIDTH,
         pos.y + R::minimap_height * (float) lowerLeft.y / MAP_HEIGHT}
    );

    left.setSize(
        {R::minimap_width * (float) (upperRight.x) / MAP_WIDTH,
         R::minimap_height * (float) (upperRight.y - lowerLeft.y) / MAP_HEIGHT}
    );
    left.setPosition(
        {pos.x + 2,
         pos.y + R::minimap_height * (float) lowerLeft.y / MAP_HEIGHT}
    );
  }
}

void Minimap::createMinimapImage(DrawableGrid *drawable_grid) {
  // отрисованная карта
  auto minimap_texture = new RenderTexture();
  minimap_texture->create(window_size.x, window_size.y);
  minimap_texture->setView(View(
      {TILE_WIDTH * (0.5f + MAP_WIDTH) / 2, 0.125f * TILE_HEIGHT * (3 * MAP_HEIGHT)},
      {TILE_WIDTH * (0.5f + MAP_WIDTH), 0.25f * TILE_HEIGHT * (3 * MAP_HEIGHT)}
  ));
  drawable_grid->renderTexture(minimap_texture, MapMode::MINIMAP, 0, MAP_WIDTH);
  minimap_texture->display();

  minimap.setTexture(minimap_texture->getTexture());
  minimap.setScale(
      {(float) R::minimap_width / minimap_texture->getTexture().getSize().x,
       (float) R::minimap_height / minimap_texture->getTexture().getSize().y}
  );
  minimap.setPosition(pos);

  overlay.setTexture(*AssetLoader::get().getTexture("minimap_overlay"));
  overlay.setScale(
      {(float) R::minimap_width / overlay.getTexture()->getSize().x,
       (float) R::minimap_height / overlay.getTexture()->getSize().y}
  );
  overlay.setPosition(pos);
}

void Minimap::createViewRectangles() {
  left.setOutlineThickness(-2);
  left.setOutlineColor(Color::White);
  left.setFillColor(Color::Transparent);

  right.setOutlineThickness(-2);
  right.setOutlineColor(Color::White);
  right.setFillColor(Color::Transparent);
}
