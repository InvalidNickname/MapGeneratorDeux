#include "GUI.h"

void GUI::render(RenderWindow *window) {
  for (auto &i : drawables) {
    i.second->render(window);
  }
}

bool GUI::checkClicked(Vector2i coords) {
  for (auto &i : drawables) {
    if (i.second->checkClicked(coords)) {
      return true;
    }
  }
  return false;
}

void GUI::addObject(const string &name, UIDrawable *drawable) {
  drawables.insert(pair(name, drawable));
}

UIDrawable *GUI::get(const string &name) const {
  return drawables.at(name);
}
