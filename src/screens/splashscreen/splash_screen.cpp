#include "splash_screen.h"

void SplashScreen::Prepare() {
  loading_thread_ = std::async(std::launch::async, [this] {
    Load();
  });
}

void SplashScreen::Load() {
  // первоначальная загрузка ассетов
  AssetLoader::Get();
}

GameState SplashScreen::DoAction() {
  Event event{};
  while (window_->pollEvent(event)) {
    if (event.type == Event::Closed) {
      temp_state_ = EXIT;
    }
  }
  auto status = loading_thread_.wait_for(0ms);
  if (status == std::future_status::ready) {
    loading_thread_.get();
    // переключение на экран настроек
    return SETTINGS;
  }
  return temp_state_;
}

void SplashScreen::Draw() {
  //TODO отрисовка загрузочного экрана
}
