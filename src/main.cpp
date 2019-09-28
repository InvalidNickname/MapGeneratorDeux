#include "main.h"

int main() {
    // установка окна
    RenderWindow window(
            VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height),
            "Map Generator",
            sf::Style::Fullscreen);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    // запуск splashscreen
    ScreenManager screenManager(new SplashScreen(&window));

    // отрисовка и прочие вещи
    while (window.isOpen()) {
        screenManager.doActiveScreenActions();
        window.clear(Color::Black);
        screenManager.drawActiveScreen();
        window.display();
    }
    return 0;
}