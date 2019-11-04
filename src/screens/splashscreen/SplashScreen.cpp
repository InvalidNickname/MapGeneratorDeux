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
  // первоначальная загрузка ресурсов
  R::get();
}

GameState SplashScreen::doAction() {
  Event event{};
  while (window->pollEvent(event)) {
    if (event.type == Event::Closed) {
      window->close();
    }
  }
  auto status = loading_thread.wait_for(0ms);
  if (status == std::future_status::ready) {
    loading_thread.get();
    // переключение на экран карты
    return MAP_SCREEN;
  }
  return THIS_STATE;
}

void SplashScreen::draw() {
  //TODO отрисовка загрузочного экрана
}
