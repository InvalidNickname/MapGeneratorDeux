#include "SplashScreen.h"

void SplashScreen::prepare() {
  loading_thread = std::async(std::launch::async, [this] {
    load();
  });
}

void SplashScreen::load() {
  // первоначальная загрузка тайлсета из json
  Tileset::get();
  // первоначальная загрузка ассетов
  AssetLoader::get();
}

GameState SplashScreen::doAction() {
  Event event{};
  while (window->pollEvent(event)) {
    if (event.type == Event::Closed) {
      temp_key = EXIT;
    }
  }
  auto status = loading_thread.wait_for(0ms);
  if (status == std::future_status::ready) {
    loading_thread.get();
    // переключение на экран настроек
    return SETTINGS;
  }
  return temp_key;
}

void SplashScreen::draw() {
  //TODO отрисовка загрузочного экрана
}
