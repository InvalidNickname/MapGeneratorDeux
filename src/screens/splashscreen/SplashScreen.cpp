#include "SplashScreen.h"

void SplashScreen::draw() {
    //TODO отрисовка загрузочного экрана
}

void SplashScreen::doAction() {
    Event event{};
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed) {
            window->close();
        }
    }
    // первоначальная загрузка тайлсета из json
    Tileset::get();
    // переключение на экран карты
    move(new MapScreen(window));
}
