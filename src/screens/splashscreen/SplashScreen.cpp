#include "SplashScreen.h"

void SplashScreen::prepare() {
  loadingThread = std::async(std::launch::async, [this] {
    load();
  });
}

void SplashScreen::load() {
  // первоначальная загрузка тайлсета из json
  Tileset::get();
  // первоначальная загрузка ассетов
  AssetLoader::get();
}

int SplashScreen::doAction() {
  Event event{};
  while (window->pollEvent(event)) {
    if (event.type == Event::Closed) {
      window->close();
    }
  }
  auto status = loadingThread.wait_for(0ms);
  if (status == std::future_status::ready) {
    loadingThread.get();
    // переключение на экран карты
    return MAP_SCREEN;
  }
  return THIS_STATE;
}

void SplashScreen::draw() {
  //TODO отрисовка загрузочного экрана
}
