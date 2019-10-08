#include "GUI.h"

GUI::GUI(uint16_t windowWidth, uint16_t windowHeight) :
        windowHeight(windowHeight), windowWidth(windowWidth) {}

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

UIDrawable *GUI::get(const string &name) {
    return drawables.at(name);
}
