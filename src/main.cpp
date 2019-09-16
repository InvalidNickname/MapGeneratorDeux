#include "main.h"

int main() {
    // установка окна
    RenderWindow window(
            VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height),
            "Map Generator",
            sf::Style::Fullscreen);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // запуск splashscreen
    ScreenManager screenManager{};
    screenManager.setActiveScreen(new SplashScreen());

    // отрисовка и прочие вещи
    while (window.isOpen()) {
        window.clear(Color::Black);
        screenManager.drawActiveScreen();
        //TODO отрисовка графики
        window.display();
    }
    return 0;
}