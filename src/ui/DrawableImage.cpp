#include "DrawableImage.h"

DrawableImage::DrawableImage(Vector2s position, Vector2s size, Texture *texture) {
  sprite_.setTexture(*texture);
  auto texture_size = texture->getSize();
  sprite_.setScale((float) size.x / texture_size.x, (float) size.y / texture_size.y);
  sprite_.setPosition(position.x, position.y);
}

void DrawableImage::render(sf::RenderWindow *window) {
  window->draw(sprite_);
}
