#include "SettingsScreen.h"

void SettingsScreen::prepare() {
  // размеры экрана
  window_size = window->getSize();
  setGUI();
  ui_view.setSize(window_size.x, window_size.y);
  ui_view.setCenter((float) window_size.x / 2, (float) window_size.y / 2);
}

void SettingsScreen::setGUI() {
  gui = new GUI();
  gui->addObject("background", new DrawableImage(
      Vector2s(0, 0),
      Vector2s(window_size.x, window_size.y),
      AssetLoader::get().getTexture("settings_background")));
  gui->addObject("height", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              100
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m2_0"),
          AssetLoader::get().getTexture("settings_height_m2_1"),
          []() {})),
      pair("-1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 2 / 5,
              100
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m1_0"),
          AssetLoader::get().getTexture("settings_height_m1_1"),
          []() {})),
      pair("0", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 3 / 5,
              100
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_0_0"),
          AssetLoader::get().getTexture("settings_height_0_1"),
          []() {})),
      pair("1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 4 / 5,
              100
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_1_0"),
          AssetLoader::get().getTexture("settings_height_1_1"),
          []() {})),
      pair("2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 5 / 5,
              100
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_2_0"),
          AssetLoader::get().getTexture("settings_height_2_1"),
          []() {}))
  }, "0"));
  // TODO кнопки настройки температуры
  gui->addObject("temperature", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m2_0"),
          AssetLoader::get().getTexture("settings_height_m2_1"),
          []() {})),
      pair("-1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 2 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m1_0"),
          AssetLoader::get().getTexture("settings_height_m1_1"),
          []() {})),
      pair("0", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 3 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_0_0"),
          AssetLoader::get().getTexture("settings_height_0_1"),
          []() {})),
      pair("1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 4 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_1_0"),
          AssetLoader::get().getTexture("settings_height_1_1"),
          []() {})),
      pair("2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 5 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_2_0"),
          AssetLoader::get().getTexture("settings_height_2_1"),
          []() {}))
  }, "0"));
  // TODO кнопки настройки влажности
  gui->addObject("moisture", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height") * 2 + 140
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m2_0"),
          AssetLoader::get().getTexture("settings_height_m2_1"),
          []() {})),
      pair("-1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 2 / 5,
              R::get().getUint("settings_radio_height") * 2 + 140
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m1_0"),
          AssetLoader::get().getTexture("settings_height_m1_1"),
          []() {})),
      pair("0", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 3 / 5,
              R::get().getUint("settings_radio_height") * 2 + 140
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_0_0"),
          AssetLoader::get().getTexture("settings_height_0_1"),
          []() {})),
      pair("1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 4 / 5,
              R::get().getUint("settings_radio_height") * 2 + 140
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_1_0"),
          AssetLoader::get().getTexture("settings_height_1_1"),
          []() {})),
      pair("2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 5 / 5,
              R::get().getUint("settings_radio_height") * 2 + 140
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_2_0"),
          AssetLoader::get().getTexture("settings_height_2_1"),
          []() {}))
  }, "0"));
  // TODO кнопки настройки размеров карты
  gui->addObject("size", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height") * 3 + 160
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m2_0"),
          AssetLoader::get().getTexture("settings_height_m2_1"),
          []() {})),
      pair("-1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 2 / 5,
              R::get().getUint("settings_radio_height") * 3 + 160
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m1_0"),
          AssetLoader::get().getTexture("settings_height_m1_1"),
          []() {})),
      pair("0", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 3 / 5,
              R::get().getUint("settings_radio_height") * 3 + 160
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_0_0"),
          AssetLoader::get().getTexture("settings_height_0_1"),
          []() {})),
      pair("1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 4 / 5,
              R::get().getUint("settings_radio_height") * 3 + 160
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_1_0"),
          AssetLoader::get().getTexture("settings_height_1_1"),
          []() {})),
      pair("2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 5 / 5,
              R::get().getUint("settings_radio_height") * 3 + 160
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_2_0"),
          AssetLoader::get().getTexture("settings_height_2_1"),
          []() {}))
  }, "0"));
  // TODO кнопки настройки сглаживания карты
  gui->addObject("flatness", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height") * 4 + 180
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m2_0"),
          AssetLoader::get().getTexture("settings_height_m2_1"),
          []() {})),
      pair("-1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 2 / 5,
              R::get().getUint("settings_radio_height") * 4 + 180
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_m1_0"),
          AssetLoader::get().getTexture("settings_height_m1_1"),
          []() {})),
      pair("0", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 3 / 5,
              R::get().getUint("settings_radio_height") * 4 + 180
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_0_0"),
          AssetLoader::get().getTexture("settings_height_0_1"),
          []() {})),
      pair("1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 4 / 5,
              R::get().getUint("settings_radio_height") * 4 + 180
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_1_0"),
          AssetLoader::get().getTexture("settings_height_1_1"),
          []() {})),
      pair("2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 5 / 5,
              R::get().getUint("settings_radio_height") * 4 + 180
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_height_2_0"),
          AssetLoader::get().getTexture("settings_height_2_1"),
          []() {}))
  }, "0"));
  // TODO кнопка генерации карты
  gui->addObject("start_gen", new Button(
      Vector2s(
          window_size.x - 200,
          R::get().getUint("settings_radio_height") * 4 + 180
      ),
      Vector2s(
          R::get().getUint("settings_radio_width") / 5,
          R::get().getUint("settings_radio_height")
      ),
      AssetLoader::get().getTexture("settings_height_2_0"),
      AssetLoader::get().getTexture("settings_height_2_1"),
      [this]() { temp_key = MAP_SCREEN; }));
}

GameState SettingsScreen::doAction() {
  handleInput();
  return temp_key;
}

void SettingsScreen::handleInput() {
  Event event{};
  while (window->pollEvent(event)) {
    if (event.type == Event::MouseButtonPressed) {
      if (Mouse::isButtonPressed(Mouse::Left)) {
        gui->checkClicked(Mouse::getPosition());
      }
    }
  }
}

void SettingsScreen::draw() {
  gui->render(window);
}
