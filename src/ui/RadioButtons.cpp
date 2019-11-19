#include "RadioButtons.h"

RadioButtons::RadioButtons(map<string, Button *> *buttons, const string &default_clicked) : buttons(buttons) {
  setClicked(default_clicked);
}

void RadioButtons::Render(RenderWindow *window) {
  for (auto &i : *buttons) {
    i.second->Render(window);
  }
}

bool RadioButtons::CheckClicked(Vector2i coords) {
  bool check = false;
  for (auto &i : *buttons) {
    if (i.second->CheckClicked(coords)) {
      clicked = i.first;
      check = true;
    }
  }
  setClicked(clicked);
  return check;
}

void RadioButtons::setClicked(const string &name) {
  clicked = name;
  for (auto &i : *buttons) {
    i.second->setClicked(false);
  }
  buttons->at(clicked)->setClicked(true);
}
