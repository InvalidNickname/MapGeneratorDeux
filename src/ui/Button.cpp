#include "Button.h"

Button::Button(Vector2s position, Vector2s size, Texture *normal, Texture *clicked, function<void()> onClick)
    : normal(normal), clicked(clicked), onClick(move(onClick)) {
  sprite.setTexture(*normal);
  auto texture_size = normal->getSize();
  sprite.setScale((float) size.x / texture_size.x, (float) size.y / texture_size.y);
  sprite.setPosition(position.x, position.y);
}

void Button::Render(RenderWindow *window) {
  window->draw(sprite);
}

bool Button::CheckClicked(Vector2i coords) {
  if (sprite.getGlobalBounds().contains(coords.x, coords.y)) {
    setClicked(true);
    return true;
  } else {
    setClicked(false);
    return false;
  }
}

void Button::setClicked(bool _clicked) {
  if (_clicked) {
    sprite.setTexture(*clicked);
    onClick();
  } else {
    sprite.setTexture(*normal);
  }
}
