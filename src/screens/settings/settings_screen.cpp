#include "settings_screen.h"

void SettingsScreen::Prepare() {
  // размеры экрана
  window_size_ = window_->getSize();
  LoadPrevSettings();
  SetGUI();
  ui_.setSize(window_size_.x, window_size_.y);
  ui_.setCenter(window_size_.x / 2.f, window_size_.y / 2.f);
}

void SettingsScreen::LoadPrevSettings() {
  // если есть файл с предыдущими настройками - читать из него, иначе из файла со стандартными настройками
  if (!GetFromJSON(ifstream("last_settings.json")) &&
      !GetFromJSON(ifstream("jsons/default_settings.json"))) {
    // TODO выкинуть исключение
  }
}

bool SettingsScreen::GetFromJSON(ifstream input) {
  if (input.good()) {
    Json base_file = Json::parse(input);
    input.close();
    settings_.insert(pair("size", base_file["size"]));
    settings_.insert(pair("temperature", base_file["temperature"]));
    settings_.insert(pair("moisture", base_file["moisture"]));
    settings_.insert(pair("ocean_level", base_file["ocean_level"]));
    settings_.insert(pair("flatness", base_file["flatness"]));
    settings_.insert(pair("generator", base_file["generator"]));
    settings_.insert(pair("seed", base_file["seed"]));
    seed = stoi(settings_.at("seed"));
    return true;
  }
  return false;
}

void SettingsScreen::SetGUI() {
  gui_ = new GUI();
  gui_->AddObject("background", new DrawableImage(
      {0, 0},
      Vector2s(window_size_.x, window_size_.y),
      AssetLoader::Get().GetTexture("s_background")));
  // кнопки настройки уровня моря
  gui_->AddObject("ocean_level_hint", new DrawableText(
      {R::kSRadioWidth / 5, 77},
      "Уровень моря",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("height", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSRadioWidth / 5, 100},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_height_-2_0"),
          AssetLoader::Get().GetTexture("s_height_-2_1"),
          [this]() { settings_["ocean_level"] = "-2"; })),
      pair("-1", new Button(
          {R::kSRadioWidth * 2 / 5, 100},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_height_-1_0"),
          AssetLoader::Get().GetTexture("s_height_-1_1"),
          [this]() { settings_["ocean_level"] = "-1"; })),
      pair("0", new Button(
          {R::kSRadioWidth * 3 / 5, 100},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_height_0_0"),
          AssetLoader::Get().GetTexture("s_height_0_1"),
          [this]() { settings_["ocean_level"] = "0"; })),
      pair("1", new Button(
          {R::kSRadioWidth * 4 / 5, 100},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_height_1_0"),
          AssetLoader::Get().GetTexture("s_height_1_1"),
          [this]() { settings_["ocean_level"] = "1"; })),
      pair("2", new Button(
          {R::kSRadioWidth, 100},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_height_2_0"),
          AssetLoader::Get().GetTexture("s_height_2_1"),
          [this]() { settings_["ocean_level"] = "2"; }))
  }, settings_["ocean_level"]));
  // кнопки настройки температуры
  gui_->AddObject("temperature_hint", new DrawableText(
      {R::kSRadioWidth / 5, R::kSRadioHeight + 97},
      "Средняя температура",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("temperature", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSRadioWidth / 5, R::kSRadioHeight + 120},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_temperature_-2_0"),
          AssetLoader::Get().GetTexture("s_temperature_-2_1"),
          [this]() { settings_["temperature"] = "-2"; })),
      pair("-1", new Button(
          {R::kSRadioWidth * 2 / 5, R::kSRadioHeight + 120},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_temperature_-1_0"),
          AssetLoader::Get().GetTexture("s_temperature_-1_1"),
          [this]() { settings_["temperature"] = "-1"; })),
      pair("0", new Button(
          {R::kSRadioWidth * 3 / 5, R::kSRadioHeight + 120},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_temperature_0_0"),
          AssetLoader::Get().GetTexture("s_temperature_0_1"),
          [this]() { settings_["temperature"] = "0"; })),
      pair("1", new Button(
          {R::kSRadioWidth * 4 / 5, R::kSRadioHeight + 120},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_temperature_1_0"),
          AssetLoader::Get().GetTexture("s_temperature_1_1"),
          [this]() { settings_["temperature"] = "1"; })),
      pair("2", new Button(
          {R::kSRadioWidth, R::kSRadioHeight + 120},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_temperature_2_0"),
          AssetLoader::Get().GetTexture("s_temperature_2_1"),
          [this]() { settings_["temperature"] = "2"; }))
  }, settings_["temperature"]));
  // кнопки настройки влажности
  gui_->AddObject("moisture_hint", new DrawableText(
      {R::kSRadioWidth / 5, R::kSRadioHeight * 2 + 117},
      "Средняя влажность",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("moisture", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSRadioWidth / 5, R::kSRadioHeight * 2 + 140},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_moisture_-2_0"),
          AssetLoader::Get().GetTexture("s_moisture_-2_1"),
          [this]() { settings_["moisture"] = "-2"; })),
      pair("-1", new Button(
          {R::kSRadioWidth * 2 / 5, R::kSRadioHeight * 2 + 140},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_moisture_-1_0"),
          AssetLoader::Get().GetTexture("s_moisture_-1_1"),
          [this]() { settings_["moisture"] = "-1"; })),
      pair("0", new Button(
          {R::kSRadioWidth * 3 / 5, R::kSRadioHeight * 2 + 140},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_moisture_0_0"),
          AssetLoader::Get().GetTexture("s_moisture_0_1"),
          [this]() { settings_["moisture"] = "0"; })),
      pair("1", new Button(
          {R::kSRadioWidth * 4 / 5, R::kSRadioHeight * 2 + 140},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_moisture_1_0"),
          AssetLoader::Get().GetTexture("s_moisture_1_1"),
          [this]() { settings_["moisture"] = "1"; })),
      pair("2", new Button(
          {R::kSRadioWidth, R::kSRadioHeight * 2 + 140},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_moisture_2_0"),
          AssetLoader::Get().GetTexture("s_moisture_2_1"),
          [this]() { settings_["moisture"] = "2"; }))
  }, settings_["moisture"]));
  // кнопки настройки размера карты
  gui_->AddObject("size_hint", new DrawableText(
      {R::kSRadioWidth / 5, R::kSRadioHeight * 4 + 157},
      "Размер карты",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("size", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSRadioWidth / 5, R::kSRadioHeight * 4 + 180},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_size_-2_0"),
          AssetLoader::Get().GetTexture("s_size_-2_1"),
          [this]() { settings_["size"] = "-2"; })),
      pair("-1", new Button(
          {R::kSRadioWidth * 2 / 5, R::kSRadioHeight * 4 + 180},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_size_-1_0"),
          AssetLoader::Get().GetTexture("s_size_-1_1"),
          [this]() { settings_["size"] = "-1"; })),
      pair("0", new Button(
          {R::kSRadioWidth * 3 / 5, R::kSRadioHeight * 4 + 180},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_size_0_0"),
          AssetLoader::Get().GetTexture("s_size_0_1"),
          [this]() { settings_["size"] = "0"; })),
      pair("1", new Button(
          {R::kSRadioWidth * 4 / 5, R::kSRadioHeight * 4 + 180},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_size_1_0"),
          AssetLoader::Get().GetTexture("s_size_1_1"),
          [this]() { settings_["size"] = "1"; })),
      pair("2", new Button(
          {R::kSRadioWidth, R::kSRadioHeight * 4 + 180},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_size_2_0"),
          AssetLoader::Get().GetTexture("s_size_2_1"),
          [this]() { settings_["size"] = "2"; }))
  }, settings_["size"]));
  // кнопки настройки сглаживания карты
  gui_->AddObject("flatness_hint", new DrawableText(
      {R::kSRadioWidth / 5, R::kSRadioHeight * 3 + 137},
      "Сглаживание карты",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("flatness", new RadioButtons(new map<string, Button *>{
      pair("-2", new Button(
          {R::kSRadioWidth / 5, R::kSRadioHeight * 3 + 160},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_flatness_-2_0"),
          AssetLoader::Get().GetTexture("s_flatness_-2_1"),
          [this]() { settings_["flatness"] = "-2"; })),
      pair("-1", new Button(
          {R::kSRadioWidth * 2 / 5, R::kSRadioHeight * 3 + 160},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_flatness_-1_0"),
          AssetLoader::Get().GetTexture("s_flatness_-1_1"),
          [this]() { settings_["flatness"] = "-1"; })),
      pair("0", new Button(
          {R::kSRadioWidth * 3 / 5, R::kSRadioHeight * 3 + 160},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_flatness_0_0"),
          AssetLoader::Get().GetTexture("s_flatness_0_1"),
          [this]() { settings_["flatness"] = "0"; })),
      pair("1", new Button(
          {R::kSRadioWidth * 4 / 5, R::kSRadioHeight * 3 + 160},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_flatness_1_0"),
          AssetLoader::Get().GetTexture("s_flatness_1_1"),
          [this]() { settings_["flatness"] = "1"; })),
      pair("2", new Button(
          {R::kSRadioWidth, R::kSRadioHeight * 3 + 160},
          {R::kSRadioWidth / 5, R::kSRadioHeight},
          AssetLoader::Get().GetTexture("s_flatness_2_0"),
          AssetLoader::Get().GetTexture("s_flatness_2_1"),
          [this]() { settings_["flatness"] = "2"; }))
  }, settings_["flatness"]));
  // TODO поле для ввода сида
  gui_->AddObject("seed_background", new DrawableImage(
      {R::kSRadioWidth * 7 / 5, R::kSRadioHeight * 5 / 2 + 140 - R::kSeedHeight / 2},
      {R::kSeedWidth, R::kSeedHeight},
      AssetLoader::Get().GetTexture("seed")
  ));
  gui_->AddObject("seed_hint", new DrawableText(
      {R::kSRadioWidth * 7 / 5, R::kSRadioHeight * 5 / 2 + 140 - R::kSeedHeight / 2 - 23},
      "Seed карты",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("seed_text_box", new DrawableText(
      {R::kSRadioWidth * 7 / 5 + 20, R::kSRadioHeight * 5 / 2 + 140 - 20},
      settings_["seed"],
      30,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  // кнопка выбора типа генератора
  gui_->AddObject("generator", new RadioButtons(new map<string, Button *>{
      pair("best", new Button(
          {R::kSRadioWidth * 7 / 5, (R::kSRadioHeight / 2 - R::kSCheckSize) / 2 + 100},
          {R::kSCheckSize, R::kSCheckSize},
          AssetLoader::Get().GetTexture("check_0"),
          AssetLoader::Get().GetTexture("check_1"),
          [this]() { settings_["generator"] = "best"; })),
      pair("perlin", new Button(
          {R::kSRadioWidth * 7 / 5, R::kSRadioHeight / 2 + (R::kSRadioHeight / 2 - R::kSCheckSize) / 2 + 100},
          {R::kSCheckSize, R::kSCheckSize},
          AssetLoader::Get().GetTexture("check_0"),
          AssetLoader::Get().GetTexture("check_1"),
          [this]() { settings_["generator"] = "perlin"; }))
  }, settings_["generator"]));
  gui_->AddObject("gen_best_text", new DrawableText(
      {R::kSRadioWidth * 7 / 5 + R::kSCheckSize + 20, (R::kSRadioHeight / 2 - R::kSCheckSize) / 2 + 100},
      "генератор v1",
      30,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  gui_->AddObject("gen_perlin_text", new DrawableText(
      {R::kSRadioWidth * 7 / 5 + R::kSCheckSize + 20,
       R::kSRadioHeight / 2 + (R::kSRadioHeight / 2 - R::kSCheckSize) / 2 + 100},
      "генератор v2",
      30,
      AssetLoader::Get().GetFont("default"),
      Color::Black
  ));
  // кнопка генерации карты
  gui_->AddObject("start_gen", new Button(
      Vector2s(
          window_size_.x - 100 - R::kGoSize,
          window_size_.y - 100 - R::kGoSize
      ),
      Vector2s(
          R::kGoSize,
          R::kGoSize
      ),
      AssetLoader::Get().GetTexture("go"),
      AssetLoader::Get().GetTexture("go"),
      [this]() {
        WriteSettings();
        temp_state_ = MAP_SCREEN;
      }));
  // кнопка выхода
  gui_->AddObject("exit", new Button(
      Vector2s(window_size_.x - R::kSCheckSize / 2, 0),
      {R::kSCheckSize / 2, R::kSCheckSize / 2},
      AssetLoader::Get().GetTexture("exit_0"),
      AssetLoader::Get().GetTexture("exit_1"),
      [this]() { temp_state_ = EXIT; }));
}

void SettingsScreen::WriteSettings() {
  settings_["seed"] = to_string(seed);
  Random::Get().SetSeed(seed);

  Json current = settings_;
  ofstream output("last_settings.json");
  output << setw(2) << current << endl;
  output.close();

  for (auto &setting : settings_) {
    if (setting.first != "generator")
      setting.second = to_string(stoi(setting.second) + 2);
  }
  G::SetIndex(settings_);
}

GameState SettingsScreen::DoAction() {
  HandleInput();
  if (seed > 0)
    ((DrawableText *) gui_->Get("seed_text_box"))->SetText(to_string(seed));
  else
    ((DrawableText *) gui_->Get("seed_text_box"))->SetText("");
  return temp_state_;
}

void SettingsScreen::HandleInput() {
  Event event{};
  while (window_->pollEvent(event)) {
    if (event.type == Event::MouseButtonPressed) {
      if (Mouse::isButtonPressed(Mouse::Left)) {
        gui_->CheckClicked(Mouse::getPosition());
      }
    }
    if (event.type == Event::Closed) {
      temp_state_ = EXIT;
    }
    if (event.type == Event::KeyPressed) {
      if (seed < 100000) {
        if (event.key.code == Keyboard::Numpad0 || event.key.code == Keyboard::Num0) seed *= 10;
        else if (event.key.code == Keyboard::Numpad1 || event.key.code == Keyboard::Num1) seed = seed * 10 + 1;
        else if (event.key.code == Keyboard::Numpad2 || event.key.code == Keyboard::Num2) seed = seed * 10 + 2;
        else if (event.key.code == Keyboard::Numpad3 || event.key.code == Keyboard::Num3) seed = seed * 10 + 3;
        else if (event.key.code == Keyboard::Numpad4 || event.key.code == Keyboard::Num4) seed = seed * 10 + 4;
        else if (event.key.code == Keyboard::Numpad5 || event.key.code == Keyboard::Num5) seed = seed * 10 + 5;
        else if (event.key.code == Keyboard::Numpad6 || event.key.code == Keyboard::Num6) seed = seed * 10 + 6;
        else if (event.key.code == Keyboard::Numpad7 || event.key.code == Keyboard::Num7) seed = seed * 10 + 7;
        else if (event.key.code == Keyboard::Numpad8 || event.key.code == Keyboard::Num8) seed = seed * 10 + 8;
        else if (event.key.code == Keyboard::Numpad9 || event.key.code == Keyboard::Num9) seed = seed * 10 + 9;
      }
      if (event.key.code == Keyboard::Backspace) seed /= 10;
    }
  }
}

void SettingsScreen::Draw() {
  gui_->Render(window_);
}
