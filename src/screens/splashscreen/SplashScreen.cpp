#include "SplashScreen.h"

SplashScreen::SplashScreen(RenderWindow *renderWindow) : Screen(renderWindow) {
    loadingThread = std::thread([this]() {
        load();
    });
}

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
    if (loadingThread.joinable()) {
        loadingThread.join();
        // переключение на экран карты
        move(new MapScreen(window));
    }
}

void SplashScreen::load() {
    // первоначальная загрузка тайлсета из json
    Tileset::get();
}
