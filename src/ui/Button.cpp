#include "Button.h"

Button::Button(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
               Texture *normal, Texture *clicked, std::function<void()> onClick)
    : x(x), y(y), width(width), height(height), normal(normal), clicked(clicked), onClick(onClick) {
  sprite.setTexture(*normal);
  auto size = sprite.getTexture()->getSize();
  sprite.setScale(width / size.x, height / size.y);
  sprite.setPosition(x, y);
}

void Button::render(RenderWindow *window) {
  window->draw(sprite);
}

bool Button::checkClicked(Vector2i coords) {
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
