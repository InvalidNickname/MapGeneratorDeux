#include "GUI.h"

GUI::GUI(float windowWidth, float windowHeight) : windowHeight(windowHeight), windowWidth(windowWidth) {}

void GUI::render(RenderWindow *window) {
    for (auto &i : drawables) {
        i.second->render(window);
    }
}

bool GUI::checkClicked(float _x, float _y) {
    for (auto &i : drawables) {
        if (i.second->checkClicked(_x, _y)) {
            return true;
        }
    }
    return false;
}

void GUI::addObject(const string &name, UIDrawable *drawable) {
    drawables.insert(pair(name, drawable));
}

UIDrawable *GUI::get(const string &name) {
    return drawables.at(name);
}
