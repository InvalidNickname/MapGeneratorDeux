#include "Minimap.h"

Minimap::Minimap(Vector2u window_size, DrawableGrid *dg) : window_size(window_size) {
  pos.x = window_size.x - R::kMinimapWidth;
  pos.y = window_size.y - R::kMinimapHeight;

  createMinimapImage(dg);
  createViewRectangles();
}

void Minimap::Render(RenderWindow *window) {
  window->draw(minimap);
  window->draw(right);
  if (left.getSize() != Vector2f(0, 0)) {
    window->draw(left);
  }
  window->draw(overlay);
}

void Minimap::updateViewRegion(Vector2s lowerLeft, Vector2s upperRight) {
  if (lowerLeft.x >= 0 && upperRight.x < G::GetMapW()) {
    right.setSize(
        {R::kMinimapWidth * (float) (upperRight.x - lowerLeft.x) / G::GetMapW(),
         R::kMinimapHeight * (float) (upperRight.y - lowerLeft.y) / G::GetMapH()}
    );
    right.setPosition(
        {pos.x + R::kMinimapWidth * (float) lowerLeft.x / G::GetMapW(),
         pos.y + R::kMinimapHeight * (float) lowerLeft.y / G::GetMapH()}
    );
    left.setSize({0, 0});
  } else {
    if (lowerLeft.x < 0) lowerLeft.x += G::GetMapW();
    if (upperRight.x >= G::GetMapW()) upperRight.x %= G::GetMapW();

    right.setSize(
        {R::kMinimapWidth * (float) (G::GetMapW() - lowerLeft.x) / G::GetMapW(),
         R::kMinimapHeight * (float) (upperRight.y - lowerLeft.y) / G::GetMapH()}
    );
    right.setPosition(
        {pos.x + R::kMinimapWidth * (float) lowerLeft.x / G::GetMapW(),
         pos.y + R::kMinimapHeight * (float) lowerLeft.y / G::GetMapH()}
    );

    left.setSize(
        {R::kMinimapWidth * (float) (upperRight.x) / G::GetMapW(),
         R::kMinimapHeight * (float) (upperRight.y - lowerLeft.y) / G::GetMapH()}
    );
    left.setPosition(
        {pos.x + 2,
         pos.y + R::kMinimapHeight * (float) lowerLeft.y / G::GetMapH()}
    );
  }
}

void Minimap::createMinimapImage(DrawableGrid *drawable_grid) {
  // отрисованная карта
  auto minimap_texture = new RenderTexture();
  minimap_texture->create(window_size.x, window_size.y);
  minimap_texture->setView(View(
      {R::kTileWidth * (0.5f + G::GetMapW()) / 2, 0.125f * R::kTileHeight * (3 * G::GetMapH())},
      {R::kTileWidth * (0.5f + G::GetMapW()), 0.25f * R::kTileHeight * (3 * G::GetMapH())}
  ));
  drawable_grid->renderTexture(minimap_texture, MapMode::MINIMAP, 0, G::GetMapW());
  minimap_texture->display();

  minimap.setTexture(minimap_texture->getTexture());
  minimap.setScale(
      {(float) R::kMinimapWidth / minimap_texture->getTexture().getSize().x,
       (float) R::kMinimapHeight / minimap_texture->getTexture().getSize().y}
  );
  minimap.setPosition(pos);

  overlay.setTexture(*AssetLoader::get().getTexture("minimap_overlay"));
  overlay.setScale(
      {(float) R::kMinimapWidth / overlay.getTexture()->getSize().x,
       (float) R::kMinimapHeight / overlay.getTexture()->getSize().y}
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
