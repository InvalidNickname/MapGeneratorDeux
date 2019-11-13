#include "MapScreen.h"

void MapScreen::prepare() {
  // размеры экрана
  window_size = window->getSize();
  // создание сетки для отрисовки
  drawable_grid = new DrawableGrid();
  // начальные размеры экрана
  initial_size = window_size / 2u;
  // установка камеры
  map_view.setSize(initial_size.x, initial_size.y);
  Vector2f camera_pos = {
      G::TILE_WIDTH * (0.5f + G::getMapW()) / 2,
      0.125f * G::TILE_HEIGHT * (3 * G::getMapH() - 2)
  };
  map_view.setCenter(camera_pos);
  // минимальный зум - сетка полностью помещается на экран по высоте
  min_zoom = camera_pos.y * 2 / (float) initial_size.y;
  map_view.zoom(min_zoom);
  zoom = min_zoom;
  // создание GUI
  setGUI();
  // установка view для интерфейса
  ui_view.setSize(window_size.x, window_size.y);
  ui_view.setCenter(initial_size.x, initial_size.y);
}

void MapScreen::setGUI() {
  gui = new GUI();
  gui->addObject("map_mode", new RadioButtons(new map<string, Button *>{
      pair("default", new Button(
          Vector2s(
              window_size.x - 5 * R::map_mode_button_width,
              window_size.y - R::minimap_height - R::map_mode_button_height
          ),
          {R::map_mode_button_width, R::map_mode_button_height},
          AssetLoader::get().getTexture("map_mode_default_0"),
          AssetLoader::get().getTexture("map_mode_default_1"),
          [this]() { map_mode = NORMAL; })),
      pair("biomes", new Button(
          Vector2s(
              window_size.x - 4 * R::map_mode_button_width,
              window_size.y - R::minimap_height - R::map_mode_button_height
          ),
          {R::map_mode_button_width, R::map_mode_button_height},
          AssetLoader::get().getTexture("map_mode_biomes_0"),
          AssetLoader::get().getTexture("map_mode_biomes_1"),
          [this]() { map_mode = BIOMES; })),
      pair("temperature", new Button(
          Vector2s(
              window_size.x - 3 * R::map_mode_button_width,
              window_size.y - R::minimap_height - R::map_mode_button_height
          ),
          {R::map_mode_button_width, R::map_mode_button_height},
          AssetLoader::get().getTexture("map_mode_temperature_0"),
          AssetLoader::get().getTexture("map_mode_temperature_1"),
          [this]() { map_mode = TEMPERATURE; })),
      pair("height", new Button(
          Vector2s(
              window_size.x - 2 * R::map_mode_button_width,
              window_size.y - R::minimap_height - R::map_mode_button_height
          ),
          {R::map_mode_button_width, R::map_mode_button_height},
          AssetLoader::get().getTexture("map_mode_height_0"),
          AssetLoader::get().getTexture("map_mode_height_1"),
          [this]() { map_mode = HEIGHT; })),
      pair("moisture", new Button(
          Vector2s(
              window_size.x - R::map_mode_button_width,
              window_size.y - R::minimap_height - R::map_mode_button_height
          ),
          {R::map_mode_button_width, R::map_mode_button_height},
          AssetLoader::get().getTexture("map_mode_moisture_0"),
          AssetLoader::get().getTexture("map_mode_moisture_1"),
          [this]() { map_mode = MOISTURE; }))
  }, "default"));
  gui->addObject("minimap", new Minimap(window_size, drawable_grid));
  gui->addObject("tile_info_list", new TileInfoList(window_size));
}

GameState MapScreen::doAction() {
  handleInput();
  return temp_key;
}

void MapScreen::handleInput() {
  Event event{};
  while (window->pollEvent(event)) {
    if (event.type == Event::MouseWheelScrolled) {
      if (event.mouseWheelScroll.delta < 0) zoom += 0.4f; else zoom -= 0.4f;
      zoomAtPoint({event.mouseWheelScroll.x, event.mouseWheelScroll.y});
    }
    if (event.type == Event::MouseButtonPressed) {
      if (Mouse::isButtonPressed(Mouse::Left)) {
        if (gui->checkClicked(Mouse::getPosition()));
        else {
          ((TileInfoList *) (gui->get("tile_info_list")))->setTile(
              drawable_grid->getTile(
                  drawable_grid->updateSelection(
                      window->mapPixelToCoords(Mouse::getPosition(), map_view))));
        }
      }
    }
    if (event.type == Event::Closed) {
      temp_key = EXIT;
    }
    // смена режимов карты
    if (Keyboard::isKeyPressed(Keyboard::Q)) {
      map_mode = MapMode::NORMAL;
      ((RadioButtons *) (gui->get("map_mode")))->setClicked("default");
    } else if (Keyboard::isKeyPressed(Keyboard::T)) {
      map_mode = MapMode::TEMPERATURE;
      ((RadioButtons *) (gui->get("map_mode")))->setClicked("temperature");
    } else if (Keyboard::isKeyPressed(Keyboard::H)) {
      map_mode = MapMode::HEIGHT;
      ((RadioButtons *) (gui->get("map_mode")))->setClicked("height");
    } else if (Keyboard::isKeyPressed(Keyboard::B)) {
      map_mode = MapMode::BIOMES;
      ((RadioButtons *) (gui->get("map_mode")))->setClicked("biomes");
    } else if (Keyboard::isKeyPressed(Keyboard::M)) {
      map_mode = MapMode::MOISTURE;
      ((RadioButtons *) (gui->get("map_mode")))->setClicked("moisture");
    }
  }
  // отдаление
  if (Keyboard::isKeyPressed(Keyboard::Subtract)) zoom += 0.06f;
  // приближение
  if (Keyboard::isKeyPressed(Keyboard::Add)) zoom -= 0.06f;
  // перемещение карты
  if (Keyboard::isKeyPressed(Keyboard::Left) || Mouse::getPosition().x < 5) {
    map_view.move(-6 * zoom, 0);
  }
  if (Keyboard::isKeyPressed(Keyboard::Right) || Mouse::getPosition().x > window_size.x - 5) {
    map_view.move(6 * zoom, 0);
  }
  if (Keyboard::isKeyPressed(Keyboard::Up) || Mouse::getPosition().y < 5) {
    map_view.move(0, -6 * zoom);
  }
  if (Keyboard::isKeyPressed(Keyboard::Down) || Mouse::getPosition().y > window_size.y - 5) {
    map_view.move(0, 6 * zoom);
  }
  // максимальный и минимальный зум
  if (zoom < 0.5) zoom = 0.5;
  if (zoom > min_zoom) zoom = min_zoom;
  // запрет на прокрутку за пределы карты по вертикали
  if (map_view.getCenter().y < 0.25f * G::TILE_HEIGHT + zoom * window_size.y / 4)
    map_view.setCenter(map_view.getCenter().x, 0.25f * G::TILE_HEIGHT + zoom * window_size.y / 4);
  if (map_view.getCenter().y > 0.75f * G::TILE_HEIGHT * G::getMapH() - zoom * window_size.y / 4)
    map_view.setCenter(map_view.getCenter().x, 0.75f * G::TILE_HEIGHT * G::getMapH() - zoom * window_size.y / 4);
  // бесконечная прокрутка по горизонтали
  if (map_view.getCenter().x <= -zoom * window_size.x / 4)
    map_view.setCenter(G::TILE_WIDTH * G::getMapW() - zoom * window_size.x / 4, map_view.getCenter().y);
  if (map_view.getCenter().x >= G::TILE_WIDTH * G::getMapW() + zoom * window_size.x / 4)
    map_view.setCenter(zoom * window_size.x / 4, map_view.getCenter().y);
}

void MapScreen::draw() {
  // отрисовка карты
  window->setView(map_view);
  auto lowerLeftTile = DrawableGrid::getTileByCoords(window->mapPixelToCoords({0, 0}));
  auto upperRightTile = DrawableGrid::getTileByCoords(window->mapPixelToCoords(Vector2i(window_size.x, window_size.y)));
  ((Minimap *) gui->get("minimap"))->updateViewRegion(lowerLeftTile, upperRightTile);
  // чтобы отрисовывать тайлы, чьи центры не попали в область отрисовки, но края все равно видны
  lowerLeftTile -= {1, 1};
  upperRightTile += {2, 2};
  // при приближении отрисовываются векторные тайлы, при отдалении - одна текстура карты
  if (zoom < 5) {
    drawable_grid->renderVector(window, map_mode, lowerLeftTile, upperRightTile);
  } else {
    drawable_grid->renderTexture(window, map_mode, lowerLeftTile.x, upperRightTile.x);
  }
  // отрисовка интерфейса
  window->setView(ui_view);
  gui->render(window);
}

void MapScreen::zoomAtPoint(Vector2i point) {
  if (zoom < 0.5) zoom = 0.5;
  if (zoom > min_zoom) zoom = min_zoom;
  // установка map_view, чтобы убедиться что расчеты не будут проведены для другого view
  window->setView(map_view);
  Vector2f worldCoordinatesBeforeZoom = window->mapPixelToCoords(point);
  map_view.setSize((float) initial_size.x * zoom, (float) initial_size.y * zoom);
  // зум
  window->setView(map_view);
  Vector2f worldCoordinatesAfterZoom = window->mapPixelToCoords(point);
  map_view.move(worldCoordinatesBeforeZoom - worldCoordinatesAfterZoom);
  window->setView(map_view);
}