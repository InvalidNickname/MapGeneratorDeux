#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "screens/screen_manager.h"
#include "screens/splashscreen/splash_screen.h"
#include "screens/map/map_screen.h"
#include "screens/settings/settings_screen.h"

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
  screen_manager.AddScreen(SETTINGS, new SettingsScreen(&window));
  screen_manager.AddScreen(SPLASHSCREEN, new SplashScreen(&window));
  screen_manager.AddScreen(MAP_SCREEN, new MapScreen(&window));

  // отрисовка и прочие вещи
  while (window.isOpen()) {
    if (screen_manager.DoActiveScreenActions()) {
      window.clear(Color::Black);
      screen_manager.DrawActiveScreen();
      window.display();
    } else {
      window.close();
    }
  }

  return 0;
}