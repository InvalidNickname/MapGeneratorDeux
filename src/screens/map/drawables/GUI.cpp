#include "GUI.h"

GUI::GUI(int windowWidth, int windowHeight) : windowHeight(windowHeight), windowWidth(windowWidth) {}

void GUI::render(RenderWindow *window) {
    for (Button *i : buttons) {
        i->render(window);
    }
}

bool GUI::checkClick(int _x, int _y) {
    bool check = false;
    for (Button *i : buttons) {
        if (i->checkClicked(_x, _y)) {
            check = true;
        }
    }
    return check;
}

void GUI::addButton(Button *button) {
    buttons.push_back(button);
}
