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
    move(new MapScreen(window));
}
