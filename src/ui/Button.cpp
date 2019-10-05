#include "Button.h"

Button::Button(float x, float y, float width, float height, Texture *normal, Texture *clicked,
               std::function<void()> onClick)
        : x(x), y(y), width(width), height(height), normal(normal), clicked(clicked), onClick(std::move(onClick)) {
    sprite.setTexture(*normal);
    auto size = sprite.getTexture()->getSize();
    sprite.setScale(width / size.x, height / size.y);
    sprite.setPosition(x, y);
}

void Button::render(RenderWindow *window) {
    window->draw(sprite);
}

bool Button::checkClicked(float _x, float _y) {
    if (_x >= x && _x <= x + width && _y >= y && _y < y + height) {
        sprite.setTexture(*clicked);
        onClick();
        return true;
    } else {
        sprite.setTexture(*normal);
        return false;
    }
}

void Button::setClicked(bool _clicked) {
    if (_clicked) {
        sprite.setTexture(*clicked);
    } else {
        sprite.setTexture(*normal);
    }
}
