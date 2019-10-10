#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <screens/ScreenManager.h>
#include <screens/splashscreen/SplashScreen.h>

using namespace sf;

int main() {
    // установка окна
    RenderWindow window(
            VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height),
            "Map Generator",
            sf::Style::Fullscreen);

    window.setFramerateLimit(60);

    // запуск splashscreen
    ScreenManager screenManager(SPLASHSCREEN, 2);
    screenManager.addScreen(SPLASHSCREEN, new SplashScreen(&window));
    screenManager.addScreen(MAP_SCREEN, new MapScreen(&window));

    Random::get().setSeed(3);

    // отрисовка и прочие вещи
    while (window.isOpen()) {
        screenManager.doActiveScreenActions();
        window.clear(Color::Black);
        screenManager.drawActiveScreen();
        window.display();
    }
    return 0;
}