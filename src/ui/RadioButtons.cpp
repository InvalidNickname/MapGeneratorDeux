#include "RadioButtons.h"

RadioButtons::RadioButtons(std::vector<Button *> buttons, int clicked) : buttons(buttons) {
    buttons.at(clicked)->setClicked(true);
}

void RadioButtons::render(RenderWindow *window) {
    for (Button *i : buttons) {
        i->render(window);
    }
}

bool RadioButtons::checkClicked(float _x, float _y) {
    bool check = false;
    for (Button *i : buttons) {
        if (i->checkClicked(_x, _y)) {
            check = true;
        }
    }
    return check;
}
