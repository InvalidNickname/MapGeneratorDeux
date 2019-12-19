#include "minimap.h"

Minimap::Minimap(Vector2u window_size, DrawableGrid *dg) : window_size_(window_size), size_(dg->GetSize()) {
  pos_.x = (float) (window_size.x - R::kMinimapWidth);
  pos_.y = (float) (window_size.y - R::kMinimapHeight);

  CreateMinimapImage(dg);
  CreateViewRectangles();
}

void Minimap::Render(RenderWindow *window) {
  window->draw(minimap_);
  window->draw(right_);
  if (left_.getSize() != Vector2f(0, 0)) {
    window->draw(left_);
  }
  window->draw(overlay_);
}

void Minimap::UpdateViewRegion(Vector2s lower_left, Vector2s upper_right) {
  if (lower_left.x >= 0 && upper_right.x < size_.x) {
    right_.setSize(
        {R::kMinimapWidth * (float) (upper_right.x - lower_left.x) / size_.x,
         R::kMinimapHeight * (float) (upper_right.y - lower_left.y) / size_.y}
    );
    right_.setPosition(
        {pos_.x + R::kMinimapWidth * (float) lower_left.x / size_.x,
         pos_.y + R::kMinimapHeight * (float) lower_left.y / size_.y}
    );
    left_.setSize({0, 0});
  } else {
    if (lower_left.x < 0) lower_left.x += size_.x;
    if (upper_right.x >= size_.x) upper_right.x %= size_.x;

    right_.setSize(
        {R::kMinimapWidth * (float) (size_.x - lower_left.x) / size_.x,
         R::kMinimapHeight * (float) (upper_right.y - lower_left.y) / size_.y}
    );
    right_.setPosition(
        {pos_.x + R::kMinimapWidth * (float) lower_left.x / size_.x,
         pos_.y + R::kMinimapHeight * (float) lower_left.y / size_.y}
    );

    left_.setSize(
        {R::kMinimapWidth * (float) (upper_right.x) / size_.x,
         R::kMinimapHeight * (float) (upper_right.y - lower_left.y) / size_.y}
    );
    left_.setPosition(
        {pos_.x + 2,
         pos_.y + R::kMinimapHeight * (float) lower_left.y / size_.y}
    );
  }
}

void Minimap::CreateMinimapImage(DrawableGrid *grid) {
  // отрисованная карта
  auto minimap_texture = new RenderTexture();
  minimap_texture->create(window_size_.x, window_size_.y);
  minimap_texture->setView(View(
      {R::kTileWidth * (0.5f + size_.x) / 2, 0.125f * R::kTileHeight * (3 * size_.y)},
      {R::kTileWidth * (0.5f + size_.x), 0.25f * R::kTileHeight * (3 * size_.y)}
  ));
  grid->RenderGridTexture(minimap_texture, MapMode::MINIMAP, 0, size_.x);
  minimap_texture->display();

  minimap_.setTexture(minimap_texture->getTexture());
  minimap_.setScale(
      {(float) R::kMinimapWidth / minimap_texture->getTexture().getSize().x,
       (float) R::kMinimapHeight / minimap_texture->getTexture().getSize().y}
  );
  minimap_.setPosition(pos_);

  overlay_.setTexture(*AssetLoader::Get().GetTexture("minimap_overlay"));
  overlay_.setScale(
      {(float) R::kMinimapWidth / overlay_.getTexture()->getSize().x,
       (float) R::kMinimapHeight / overlay_.getTexture()->getSize().y}
  );
  overlay_.setPosition(pos_);
}

void Minimap::CreateViewRectangles() {
  left_.setOutlineThickness(-2);
  left_.setOutlineColor(Color::White);
  left_.setFillColor(Color::Transparent);

  right_.setOutlineThickness(-2);
  right_.setOutlineColor(Color::White);
  right_.setFillColor(Color::Transparent);
}
