#include "SettingsScreen.h"

void SettingsScreen::prepare() {
  // размеры экрана
  window_size = window->getSize();
  loadPrevSettings();
  setGUI();
  ui_view.setSize(window_size.x, window_size.y);
  ui_view.setCenter(window_size.x / 2.f, window_size.y / 2.f);
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
    settings.insert(pair("size", base_file["size"]));
    settings.insert(pair("temperature", base_file["temperature"]));
    settings.insert(pair("moisture", base_file["moisture"]));
    settings.insert(pair("ocean_level", base_file["ocean_level"]));
    settings.insert(pair("flatness", base_file["flatness"]));
    settings.insert(pair("generator", base_file["generator"]));
    return true;
  }
  return false;
}

void SettingsScreen::setGUI() {
  gui = new GUI();
  gui->addObject("background", new DrawableImage(
      {0, 0},
      Vector2s(window_size.x, window_size.y),
      AssetLoader::get().getTexture("s_background")));
  gui->addObject("height", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSettingsRadioWidth / 5, 100},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-2_0"),
          AssetLoader::get().getTexture("s_height_-2_1"),
          [this]() { settings["ocean_level"] = "-2"; })),
      pair("-1", new Button(
          {R::kSettingsRadioWidth * 2 / 5, 100},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-1_0"),
          AssetLoader::get().getTexture("s_height_-1_1"),
          [this]() { settings["ocean_level"] = "-1"; })),
      pair("0", new Button(
          {R::kSettingsRadioWidth * 3 / 5, 100},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_0_0"),
          AssetLoader::get().getTexture("s_height_0_1"),
          [this]() { settings["ocean_level"] = "0"; })),
      pair("1", new Button(
          {R::kSettingsRadioWidth * 4 / 5, 100},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_1_0"),
          AssetLoader::get().getTexture("s_height_1_1"),
          [this]() { settings["ocean_level"] = "1"; })),
      pair("2", new Button(
          {R::kSettingsRadioWidth, 100},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_2_0"),
          AssetLoader::get().getTexture("s_height_2_1"),
          [this]() { settings["ocean_level"] = "2"; }))
  }, settings["ocean_level"]));
  gui->addObject("temperature", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight + 120},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_temperature_-2_0"),
          AssetLoader::get().getTexture("s_temperature_-2_1"),
          [this]() { settings["temperature"] = "-2"; })),
      pair("-1", new Button(
          {R::kSettingsRadioWidth * 2 / 5, R::kSettingsRadioHeight + 120},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_temperature_-1_0"),
          AssetLoader::get().getTexture("s_temperature_-1_1"),
          [this]() { settings["temperature"] = "-1"; })),
      pair("0", new Button(
          {R::kSettingsRadioWidth * 3 / 5, R::kSettingsRadioHeight + 120},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_temperature_0_0"),
          AssetLoader::get().getTexture("s_temperature_0_1"),
          [this]() { settings["temperature"] = "0"; })),
      pair("1", new Button(
          {R::kSettingsRadioWidth * 4 / 5, R::kSettingsRadioHeight + 120},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_temperature_1_0"),
          AssetLoader::get().getTexture("s_temperature_1_1"),
          [this]() { settings["temperature"] = "1"; })),
      pair("2", new Button(
          {R::kSettingsRadioWidth, R::kSettingsRadioHeight + 120},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_temperature_2_0"),
          AssetLoader::get().getTexture("s_temperature_2_1"),
          [this]() { settings["temperature"] = "2"; }))
  }, settings["temperature"]));
  // TODO кнопки настройки влажности
  gui->addObject("moisture", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight * 2 + 140},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-2_0"),
          AssetLoader::get().getTexture("s_height_-2_1"),
          [this]() { settings["moisture"] = "-2"; })),
      pair("-1", new Button(
          {R::kSettingsRadioWidth * 2 / 5, R::kSettingsRadioHeight * 2 + 140},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-1_0"),
          AssetLoader::get().getTexture("s_height_-1_1"),
          [this]() { settings["moisture"] = "-1"; })),
      pair("0", new Button(
          {R::kSettingsRadioWidth * 3 / 5, R::kSettingsRadioHeight * 2 + 140},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_0_0"),
          AssetLoader::get().getTexture("s_height_0_1"),
          [this]() { settings["moisture"] = "0"; })),
      pair("1", new Button(
          {R::kSettingsRadioWidth * 4 / 5, R::kSettingsRadioHeight * 2 + 140},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_1_0"),
          AssetLoader::get().getTexture("s_height_1_1"),
          [this]() { settings["moisture"] = "1"; })),
      pair("2", new Button(
          {R::kSettingsRadioWidth, R::kSettingsRadioHeight * 2 + 140},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_2_0"),
          AssetLoader::get().getTexture("s_height_2_1"),
          [this]() { settings["moisture"] = "2"; }))
  }, settings["moisture"]));
  gui->addObject("size", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight * 3 + 160},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_size_-2_0"),
          AssetLoader::get().getTexture("s_size_-2_1"),
          [this]() { settings["size"] = "-2"; })),
      pair("-1", new Button(
          {R::kSettingsRadioWidth * 2 / 5, R::kSettingsRadioHeight * 3 + 160},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_size_-1_0"),
          AssetLoader::get().getTexture("s_size_-1_1"),
          [this]() { settings["size"] = "-1"; })),
      pair("0", new Button(
          {R::kSettingsRadioWidth * 3 / 5, R::kSettingsRadioHeight * 3 + 160},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_size_0_0"),
          AssetLoader::get().getTexture("s_size_0_1"),
          [this]() { settings["size"] = "0"; })),
      pair("1", new Button(
          {R::kSettingsRadioWidth * 4 / 5, R::kSettingsRadioHeight * 3 + 160},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_size_1_0"),
          AssetLoader::get().getTexture("s_size_1_1"),
          [this]() { settings["size"] = "1"; })),
      pair("2", new Button(
          {R::kSettingsRadioWidth, R::kSettingsRadioHeight * 3 + 160},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_size_2_0"),
          AssetLoader::get().getTexture("s_size_2_1"),
          [this]() { settings["size"] = "2"; }))
  }, settings["size"]));
  // TODO кнопки настройки сглаживания карты
  gui->addObject("flatness", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-2_0"),
          AssetLoader::get().getTexture("s_height_-2_1"),
          [this]() { settings["flatness"] = "-2"; })),
      pair("-1", new Button(
          {R::kSettingsRadioWidth * 2 / 5, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-1_0"),
          AssetLoader::get().getTexture("s_height_-1_1"),
          [this]() { settings["flatness"] = "-1"; })),
      pair("0", new Button(
          {R::kSettingsRadioWidth * 3 / 5, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_0_0"),
          AssetLoader::get().getTexture("s_height_0_1"),
          [this]() { settings["flatness"] = "0"; })),
      pair("1", new Button(
          {R::kSettingsRadioWidth * 4 / 5, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_1_0"),
          AssetLoader::get().getTexture("s_height_1_1"),
          [this]() { settings["flatness"] = "1"; })),
      pair("2", new Button(
          {R::kSettingsRadioWidth, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_2_0"),
          AssetLoader::get().getTexture("s_height_2_1"),
          [this]() { settings["flatness"] = "2"; }))
  }, settings["flatness"]));
  // TODO поле для ввода сида
  // TODO кнопка выбора типа генератора
  gui->addObject("generator", new RadioButtons(new map<string, Button *>{
      pair("best", new Button(
          {R::kSettingsRadioWidth * 7 / 5, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-2_0"),
          AssetLoader::get().getTexture("s_height_-2_1"),
          [this]() { settings["generator"] = "best"; })),
      pair("perlin", new Button(
          {R::kSettingsRadioWidth * 8 / 5, R::kSettingsRadioHeight * 4 + 180},
          {R::kSettingsRadioWidth / 5, R::kSettingsRadioHeight},
          AssetLoader::get().getTexture("s_height_-1_0"),
          AssetLoader::get().getTexture("s_height_-1_1"),
          [this]() { settings["generator"] = "perlin"; }))
  }, settings["generator"]));
  // TODO кнопка генерации карты
  gui->addObject("start_gen", new Button(
      Vector2s(
          window_size.x - 200,
          R::kSettingsRadioHeight * 4 + 180
      ),
      Vector2s(
          R::kSettingsRadioWidth / 5,
          R::kSettingsRadioHeight
      ),
      AssetLoader::get().getTexture("s_height_2_0"),
      AssetLoader::get().getTexture("s_height_2_1"),
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

  for (auto &setting : settings) {
    if (setting.first != "generator")
      setting.second = to_string(stoi(setting.second) + 2);
  }
  G::SetIndex(settings);
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
    if (event.type == Event::Closed) {
      temp_key = EXIT;
    }
  }
}

void SettingsScreen::draw() {
  gui->render(window);
}
