#include "RadioButtons.h"

RadioButtons::RadioButtons(map<string, Button *> *buttons, const string &name) : buttons(buttons) {
    setClicked(name);
}

void RadioButtons::render(RenderWindow *window) {
    for (auto &i : *buttons) {
        i.second->render(window);
    }
}

bool RadioButtons::checkClicked(Vector2i coords) {
    bool check = false;
    for (auto &i : *buttons) {
        if (i.second->checkClicked(coords)) {
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
