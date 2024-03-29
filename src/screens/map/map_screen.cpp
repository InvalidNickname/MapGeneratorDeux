#include "map_screen.h"

void MapScreen::Prepare() {
  // размеры экрана
  window_size_ = window_->getSize();
  // создание сетки для отрисовки
  grid_ = new DrawableGrid();
  // начальные размеры экрана
  initial_size_ = window_size_ / 2u;
  // установка камеры
  map_.setSize((float) initial_size_.x, (float) initial_size_.y);
  Vector2f camera_pos = {
      0.5f * R::kTileWidth * (0.5f + grid_->GetSize().x),
      0.125f * R::kTileHeight * (3.f * grid_->GetSize().y - 1.f)
  };
  map_.setCenter(camera_pos);
  // минимальный зум - сетка полностью помещается на экран по высоте
  min_zoom_ = 2.f * camera_pos.y / initial_size_.y;
  map_.zoom(min_zoom_);
  zoom_ = min_zoom_;
  // создание GUI
  SetGUI();
  // установка view для интерфейса
  ui_.setSize((Vector2f) window_size_);
  ui_.setCenter((Vector2f) initial_size_);
}

void MapScreen::SetGUI() {
  gui_ = new GUI();
  gui_->AddObject("map_mode", new RadioButtons(new map<string, Button *>{
      pair("default", new Button(
          {(float) window_size_.x - 5 * R::kMapModeButtonWidth,
           (float) window_size_.y - R::kMinimapHeight - R::kMapModeButtonHeight},
          {R::kMapModeButtonWidth, R::kMapModeButtonHeight},
          AssetLoader::Get().GetTexture("map_mode_default_0"),
          AssetLoader::Get().GetTexture("map_mode_default_1"),
          [this]() { map_mode_ = NORMAL; })),
      pair("biomes", new Button(
          {(float) window_size_.x - 4 * R::kMapModeButtonWidth,
           (float) window_size_.y - R::kMinimapHeight - R::kMapModeButtonHeight},
          {R::kMapModeButtonWidth, R::kMapModeButtonHeight},
          AssetLoader::Get().GetTexture("map_mode_biomes_0"),
          AssetLoader::Get().GetTexture("map_mode_biomes_1"),
          [this]() { map_mode_ = BIOMES; })),
      pair("temperature", new Button(
          {(float) window_size_.x - 3 * R::kMapModeButtonWidth,
           (float) window_size_.y - R::kMinimapHeight - R::kMapModeButtonHeight},
          {R::kMapModeButtonWidth, R::kMapModeButtonHeight},
          AssetLoader::Get().GetTexture("map_mode_temperature_0"),
          AssetLoader::Get().GetTexture("map_mode_temperature_1"),
          [this]() { map_mode_ = TEMPERATURE; })),
      pair("height", new Button(
          {(float) window_size_.x - 2 * R::kMapModeButtonWidth,
           (float) window_size_.y - R::kMinimapHeight - R::kMapModeButtonHeight},
          {R::kMapModeButtonWidth, R::kMapModeButtonHeight},
          AssetLoader::Get().GetTexture("map_mode_height_0"),
          AssetLoader::Get().GetTexture("map_mode_height_1"),
          [this]() { map_mode_ = HEIGHT; })),
      pair("moisture", new Button(
          {(float) window_size_.x - R::kMapModeButtonWidth,
           (float) window_size_.y - R::kMinimapHeight - R::kMapModeButtonHeight},
          {R::kMapModeButtonWidth, R::kMapModeButtonHeight},
          AssetLoader::Get().GetTexture("map_mode_moisture_0"),
          AssetLoader::Get().GetTexture("map_mode_moisture_1"),
          [this]() { map_mode_ = MOISTURE; }))
  }, "default"));
  gui_->AddObject("minimap", new Minimap(window_size_, grid_));
  gui_->AddObject("info_coords", new DrawableText(
      {20.f, window_size_.y - 60.f},
      "",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::White));
  gui_->AddObject("info_type", new DrawableText(
      {20.f, window_size_.y - 95.f},
      "",
      30,
      AssetLoader::Get().GetFont("default"),
      Color::White));
  gui_->AddObject("info_temperature", new DrawableText(
      {20.f, window_size_.y - 40.f},
      "",
      20,
      AssetLoader::Get().GetFont("default"),
      Color::White));
  // кнопка выхода
  gui_->AddObject("exit", new Button(
      {window_size_.x - R::kSCheckSize / 2.f, 0},
      {R::kSCheckSize / 2.f, R::kSCheckSize / 2.f},
      AssetLoader::Get().GetTexture("exit_0"),
      AssetLoader::Get().GetTexture("exit_1"),
      [this]() { temp_state_ = EXIT; }));
}

GameState MapScreen::DoAction() {
  HandleInput();
  return temp_state_;
}

void MapScreen::HandleInput() {
  Event event{};
  while (window_->pollEvent(event)) {
    if (event.type == Event::MouseWheelScrolled) {
      if (event.mouseWheelScroll.delta < 0) zoom_ += 0.4f; else zoom_ -= 0.4f;
      ZoomAtPoint({event.mouseWheelScroll.x, event.mouseWheelScroll.y});
    }
    if (event.type == Event::MouseButtonPressed) {
      if (Mouse::isButtonPressed(Mouse::Left)) {
        if (gui_->CheckClicked((Vector2f) Mouse::getPosition()));
        else {
          Tile *tile = grid_->GetTile(grid_->UpdateSelection(
              window_->mapPixelToCoords(Mouse::getPosition(), map_)));
          ((DrawableText *) gui_->Get("info_type"))->SetText(tile->GetType()->GetName(tile->GetLevel()));
          ((DrawableText *) gui_->Get("info_temperature"))->SetText(
              to_string(tile->GetTemperature() - 273).append(" °C"));
          string latitudeText
              (to_string((int) tile->latitude_).append((tile->pos_.y < grid_->GetSize().y / 2u ? " °N" : " °S")));
          string longitudeText
              (to_string((int) tile->longitude_).append((tile->pos_.x > grid_->GetSize().x / 2u ? " °E" : " °W")));
          ((DrawableText *) gui_->Get("info_coords"))->SetText(latitudeText.append(" ").append(longitudeText));
        }
      }
    }
    if (event.type == Event::Closed) {
      temp_state_ = EXIT;
    }
    // смена режимов карты
    if (Keyboard::isKeyPressed(Keyboard::Q)) {
      map_mode_ = MapMode::NORMAL;
      ((RadioButtons *) gui_->Get("map_mode"))->SetClicked("default");
    } else if (Keyboard::isKeyPressed(Keyboard::T)) {
      map_mode_ = MapMode::TEMPERATURE;
      ((RadioButtons *) gui_->Get("map_mode"))->SetClicked("temperature");
    } else if (Keyboard::isKeyPressed(Keyboard::H)) {
      map_mode_ = MapMode::HEIGHT;
      ((RadioButtons *) gui_->Get("map_mode"))->SetClicked("height");
    } else if (Keyboard::isKeyPressed(Keyboard::B)) {
      map_mode_ = MapMode::BIOMES;
      ((RadioButtons *) gui_->Get("map_mode"))->SetClicked("biomes");
    } else if (Keyboard::isKeyPressed(Keyboard::M)) {
      map_mode_ = MapMode::MOISTURE;
      ((RadioButtons *) gui_->Get("map_mode"))->SetClicked("moisture");
    }
  }
  // отдаление
  if (Keyboard::isKeyPressed(Keyboard::Subtract)) zoom_ += 0.06f;
  // приближение
  if (Keyboard::isKeyPressed(Keyboard::Add)) zoom_ -= 0.06f;
  // перемещение карты
  if (Keyboard::isKeyPressed(Keyboard::Left) || Mouse::getPosition().x < 5) {
    map_.move(-6 * zoom_, 0);
  }
  if (Keyboard::isKeyPressed(Keyboard::Right) || Mouse::getPosition().x > window_size_.x - 5u) {
    map_.move(6 * zoom_, 0);
  }
  if (Keyboard::isKeyPressed(Keyboard::Up) || Mouse::getPosition().y < 5) {
    map_.move(0, -6 * zoom_);
  }
  if (Keyboard::isKeyPressed(Keyboard::Down) || Mouse::getPosition().y > window_size_.y - 5u) {
    map_.move(0, 6 * zoom_);
  }
  // максимальный и минимальный зум
  if (zoom_ < 0.5) zoom_ = 0.5;
  if (zoom_ > min_zoom_) zoom_ = min_zoom_;
  // запрет на прокрутку за пределы карты по вертикали
  if (map_.getCenter().y < 0.25f * R::kTileHeight + zoom_ * window_size_.y / 4)
    map_.setCenter(map_.getCenter().x, 0.25f * R::kTileHeight + zoom_ * window_size_.y / 4);
  if (map_.getCenter().y > 0.75f * R::kTileHeight * grid_->GetSize().y - zoom_ * window_size_.y / 4)
    map_.setCenter(map_.getCenter().x, 0.75f * R::kTileHeight * grid_->GetSize().y - zoom_ * window_size_.y / 4);
  // бесконечная прокрутка по горизонтали
  if (map_.getCenter().x <= -zoom_ * window_size_.x / 4)
    map_.setCenter(R::kTileWidth * grid_->GetSize().x - zoom_ * window_size_.x / 4, map_.getCenter().y);
  if (map_.getCenter().x >= R::kTileWidth * grid_->GetSize().x + zoom_ * window_size_.x / 4)
    map_.setCenter(zoom_ * window_size_.x / 4, map_.getCenter().y);
}

void MapScreen::Draw() {
  // отрисовка карты
  window_->setView(map_);
  auto lowerLeftTile = DrawableGrid::GetTileByCoords(window_->mapPixelToCoords({0, 0}));
  auto upperRightTile =
      DrawableGrid::GetTileByCoords(window_->mapPixelToCoords(Vector2i(window_size_.x, window_size_.y)));
  ((Minimap *) gui_->Get("minimap"))->UpdateViewRegion(lowerLeftTile, upperRightTile);
  // чтобы отрисовывать тайлы, чьи центры не попали в область отрисовки, но края все равно видны
  lowerLeftTile -= {1, 1};
  upperRightTile += {2, 2};
  // при приближении отрисовываются векторные тайлы, при отдалении - одна текстура карты
  if (zoom_ < 5) {
    grid_->RenderVector(window_, map_mode_, lowerLeftTile, upperRightTile);
  } else {
    grid_->RenderGridTexture(window_, map_mode_, lowerLeftTile.x, upperRightTile.x);
  }
  // отрисовка интерфейса
  window_->setView(ui_);
  gui_->Render(window_);
}

void MapScreen::ZoomAtPoint(Vector2i point) {
  if (zoom_ < 0.5) zoom_ = 0.5;
  if (zoom_ > min_zoom_) zoom_ = min_zoom_;
  // установка map_, чтобы убедиться что расчеты не будут проведены для другого view
  window_->setView(map_);
  Vector2f worldCoordinatesBeforeZoom = window_->mapPixelToCoords(point);
  map_.setSize((float) initial_size_.x * zoom_, (float) initial_size_.y * zoom_);
  // зум
  window_->setView(map_);
  Vector2f worldCoordinatesAfterZoom = window_->mapPixelToCoords(point);
  map_.move(worldCoordinatesBeforeZoom - worldCoordinatesAfterZoom);
  window_->setView(map_);
}