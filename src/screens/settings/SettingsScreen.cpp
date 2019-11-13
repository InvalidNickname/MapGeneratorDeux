#include "SettingsScreen.h"

void SettingsScreen::prepare() {
  // размеры экрана
  window_size = window->getSize();
  loadPrevSettings();
  setGUI();
  ui_view.setSize(window_size.x, window_size.y);
  ui_view.setCenter((float) window_size.x / 2, (float) window_size.y / 2);
}

void SettingsScreen::loadPrevSettings() {
  // если есть файл с предыдущими настройками - читать из него, иначе из файла со стандартными настройками
  if (!getFromJSON(ifstream("last_settings.json")) &&
      !getFromJSON(ifstream("jsons/default_settings.json"))) {
    // TODO выкинуть исключение
  }
}

bool SettingsScreen::getFromJSON(ifstream input) {
  if (input.good()) {
    Json base_file = Json::parse(input);
    input.close();
    settings.insert(pair("size", base_file.at("size")));
    settings.insert(pair("temperature", base_file.at("temperature")));
    settings.insert(pair("moisture", base_file.at("moisture")));
    settings.insert(pair("ocean_level", base_file.at("ocean_level")));
    settings.insert(pair("flatness", base_file.at("flatness")));
    return true;
  }
  return false;
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
          [this]() { settings["ocean_level"] = -2; })),
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
          [this]() { settings["ocean_level"] = -1; })),
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
          [this]() { settings["ocean_level"] = 0; })),
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
          [this]() { settings["ocean_level"] = 1; })),
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
          [this]() { settings["ocean_level"] = 2; }))
  }, to_string(settings.at("ocean_level"))));
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
          AssetLoader::get().getTexture("settings_temperature_m2_0"),
          AssetLoader::get().getTexture("settings_temperature_m2_1"),
          [this]() { settings["temperature"] = -2; })),
      pair("-1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 2 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_temperature_m1_0"),
          AssetLoader::get().getTexture("settings_temperature_m1_1"),
          [this]() { settings["temperature"] = -1; })),
      pair("0", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 3 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_temperature_0_0"),
          AssetLoader::get().getTexture("settings_temperature_0_1"),
          [this]() { settings["temperature"] = 0; })),
      pair("1", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 4 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_temperature_1_0"),
          AssetLoader::get().getTexture("settings_temperature_1_1"),
          [this]() { settings["temperature"] = 1; })),
      pair("2", new Button(
          Vector2s(
              R::get().getUint("settings_radio_width") * 5 / 5,
              R::get().getUint("settings_radio_height") + 120
          ),
          Vector2s(
              R::get().getUint("settings_radio_width") / 5,
              R::get().getUint("settings_radio_height")
          ),
          AssetLoader::get().getTexture("settings_temperature_2_0"),
          AssetLoader::get().getTexture("settings_temperature_2_1"),
          [this]() { settings["temperature"] = 2; }))
  }, to_string(settings.at("temperature"))));
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
          [this]() { settings["moisture"] = -2; })),
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
          [this]() { settings["moisture"] = -1; })),
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
          [this]() { settings["moisture"] = 0; })),
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
          [this]() { settings["moisture"] = 1; })),
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
          [this]() { settings["moisture"] = 2; }))
  }, to_string(settings.at("moisture"))));
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
          [this]() { settings["size"] = -2; })),
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
          [this]() { settings["size"] = -1; })),
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
          [this]() { settings["size"] = 0; })),
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
          [this]() { settings["size"] = 1; })),
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
          [this]() { settings["size"] = 2; }))
  }, to_string(settings.at("size"))));
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
          [this]() { settings["flatness"] = -2; })),
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
          [this]() { settings["flatness"] = -1; })),
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
          [this]() { settings["flatness"] = 0; })),
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
          [this]() { settings["flatness"] = 1; })),
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
          [this]() { settings["flatness"] = 2; }))
  }, to_string(settings.at("flatness"))));
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
      [this]() {
        writeSettings();
        temp_key = MAP_SCREEN;
      }));
}

void SettingsScreen::writeSettings() {
  Json current = settings;
  ofstream output("last_settings.json");
  output << setw(2) << current << endl;
  output.close();
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
