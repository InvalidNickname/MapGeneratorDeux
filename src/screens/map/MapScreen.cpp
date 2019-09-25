#include "MapScreen.h"

void MapScreen::draw() {
    //TODO отрисовка карты
}

void MapScreen::doAction() {
    Event event{};
    while (window->pollEvent(event)) {
        //TODO события при экране карты
    }
}
