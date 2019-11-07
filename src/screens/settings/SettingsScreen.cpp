#include "SettingsScreen.h"

void SettingsScreen::prepare() {
  // размеры экрана
  window_height = window->getSize().y;
  window_width = window->getSize().x;
  setGUI();
  ui_view.setSize(window_width, window_height);
  ui_view.setCenter((float) window_width / 2, (float) window_height / 2);
}

void SettingsScreen::setGUI() {
  gui = new GUI();
  gui->addObject("background", new DrawableImage(
      Vector2s(0, 0),
      Vector2s(window_width, window_height),
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
}

GameState SettingsScreen::doAction() {
  handleInput();
  return THIS_STATE;
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
