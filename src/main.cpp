#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "screens/ScreenManager.h"
#include "screens/splashscreen/SplashScreen.h"
#include "screens/map/MapScreen.h"
#include "screens/settings/SettingsScreen.h"

using namespace sf;

int main() {
  // установка окна
  RenderWindow window(
      VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height),
      "Map Generator",
      sf::Style::Fullscreen);

  window.setFramerateLimit(60);

  // запуск splashscreen
  ScreenManager screen_manager(SPLASHSCREEN, 3);
  screen_manager.addScreen(SETTINGS, new SettingsScreen(&window));
  screen_manager.addScreen(SPLASHSCREEN, new SplashScreen(&window));
  screen_manager.addScreen(MAP_SCREEN, new MapScreen(&window));

  Random::get().setSeed(3);

  // отрисовка и прочие вещи
  while (window.isOpen()) {
    screen_manager.doActiveScreenActions();
    window.clear(Color::Black);
    screen_manager.drawActiveScreen();
    window.display();
  }
  return 0;
}