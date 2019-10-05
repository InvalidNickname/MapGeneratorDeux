#include "GUI.h"

GUI::GUI(float windowWidth, float windowHeight) : windowHeight(windowHeight), windowWidth(windowWidth) {}

void GUI::render(RenderWindow *window) {
    for (UIDrawable *i : drawables) {
        i->render(window);
    }
}

bool GUI::checkClicked(float _x, float _y) {
    for (UIDrawable *i : drawables) {
        if (i->checkClicked(_x, _y)) {
            return true;
        }
    }
    return false;
}

void GUI::addDrawables(UIDrawable *drawable) {
    drawables.push_back(drawable);
}
