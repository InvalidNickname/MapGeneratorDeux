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
  if (lowerLeft.x >= 0 && upperRight.x < G::getMapW()) {
    right.setSize(
        {R::minimap_width * (float) (upperRight.x - lowerLeft.x) / G::getMapW(),
         R::minimap_height * (float) (upperRight.y - lowerLeft.y) / G::getMapH()}
    );
    right.setPosition(
        {pos.x + R::minimap_width * (float) lowerLeft.x / G::getMapW(),
         pos.y + R::minimap_height * (float) lowerLeft.y / G::getMapH()}
    );
    left.setSize({0, 0});
  } else {
    if (lowerLeft.x < 0) lowerLeft.x += G::getMapW();
    if (upperRight.x >= G::getMapW()) upperRight.x %= G::getMapW();

    right.setSize(
        {R::minimap_width * (float) (G::getMapW() - lowerLeft.x) / G::getMapW(),
         R::minimap_height * (float) (upperRight.y - lowerLeft.y) / G::getMapH()}
    );
    right.setPosition(
        {pos.x + R::minimap_width * (float) lowerLeft.x / G::getMapW(),
         pos.y + R::minimap_height * (float) lowerLeft.y / G::getMapH()}
    );

    left.setSize(
        {R::minimap_width * (float) (upperRight.x) / G::getMapW(),
         R::minimap_height * (float) (upperRight.y - lowerLeft.y) / G::getMapH()}
    );
    left.setPosition(
        {pos.x + 2,
         pos.y + R::minimap_height * (float) lowerLeft.y / G::getMapH()}
    );
  }
}

void Minimap::createMinimapImage(DrawableGrid *drawable_grid) {
  // отрисованная карта
  auto minimap_texture = new RenderTexture();
  minimap_texture->create(window_size.x, window_size.y);
  minimap_texture->setView(View(
      {G::TILE_WIDTH * (0.5f + G::getMapW()) / 2, 0.125f * G::TILE_HEIGHT * (3 * G::getMapH())},
      {G::TILE_WIDTH * (0.5f + G::getMapW()), 0.25f * G::TILE_HEIGHT * (3 * G::getMapH())}
  ));
  drawable_grid->renderTexture(minimap_texture, MapMode::MINIMAP, 0, G::getMapW());
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
