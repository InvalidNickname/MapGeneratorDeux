#include "RadioButtons.h"

RadioButtons::RadioButtons(map<string, Button *> *buttons, const string &name) : buttons(buttons) {
    buttons->at(name)->setClicked(true);
}

void RadioButtons::render(RenderWindow *window) {
    for (auto &i : *buttons) {
        i.second->render(window);
    }
}

bool RadioButtons::checkClicked(float _x, float _y) {
    bool check = false;
    for (auto &i : *buttons) {
        if (i.second->checkClicked(_x, _y)) {
            check = true;
        }
    }
    return check;
}

void RadioButtons::setClicked(const string &name) {
    for (auto &i : *buttons) {
        i.second->setClicked(false);
    }
    buttons->at(name)->setClicked(true);
}
