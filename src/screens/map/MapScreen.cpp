#include "MapScreen.h"

void MapScreen::prepare() {
    // размеры экрана
    windowHeight = window->getSize().y;
    windowWidth = window->getSize().x;
    // создание сетки для отрисовки
    drawableGrid = new DrawableGrid();
    // начальные размеры экрана
    initialHeight = windowHeight / 2.f;
    initialWidth = windowWidth / 2.f;
    // установка камеры
    mapView.setSize(initialWidth, initialHeight);
    float camX = TILE_WIDTH * (0.5f + MAP_WIDTH) / 2;
    float camY = 0.125f * TILE_HEIGHT * (1 + 3 * MAP_HEIGHT);
    mapView.setCenter(camX, camY);
    // минимальный зум - сетка полностью помещается на экран по высоте
    minZoom = camY * 2 / initialHeight;
    mapView.zoom(minZoom);
    zoom = minZoom;
    // создание GUI
    setGUI();
    // установка view для интерфейса
    uiView.setSize(windowWidth, windowHeight);
    uiView.setCenter(initialWidth, initialHeight);
}

void MapScreen::setGUI() {
    gui = new GUI(windowWidth, windowHeight);
    gui->addButton(new Button(
            windowWidth - 41 - 41, windowHeight - 200 - 31, 41, 31,
            AssetLoader::get().getTexture("map_mode_default_0"), AssetLoader::get().getTexture("map_mode_default_1"),
            [this]() { mapMode = MapMode::NORMAL; }));
    gui->addButton(new Button(
            windowWidth - 41, windowHeight - 200 - 31, 41, 31,
            AssetLoader::get().getTexture("map_mode_biomes_0"), AssetLoader::get().getTexture("map_mode_biomes_1"),
            [this]() { mapMode = MapMode::BIOMES; }));
}

int MapScreen::doAction() {
    handleInput();
    return THIS_STATE;
}

void MapScreen::handleInput() {
    Event event{};
    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta < 0) zoom += 0.4f;
                else zoom -= 0.4f;
                zoomAtPoint({event.mouseWheelScroll.x, event.mouseWheelScroll.y});
                break;
        }
    }
    if (Mouse::isButtonPressed(Mouse::Left)) {
        gui->checkClick(Mouse::getPosition().x, Mouse::getPosition().y);
    }
    // смена режимов карты
    if (Keyboard::isKeyPressed(Keyboard::Q)) mapMode = MapMode::NORMAL;
    else if (Keyboard::isKeyPressed(Keyboard::T)) mapMode = MapMode::TEMPERATURE;
    else if (Keyboard::isKeyPressed(Keyboard::H)) mapMode = MapMode::HEIGHT;
    else if (Keyboard::isKeyPressed(Keyboard::B)) mapMode = MapMode::BIOMES;
    // отдаление
    if (Keyboard::isKeyPressed(Keyboard::Subtract)) zoom += 0.06f;
    // приближение
    if (Keyboard::isKeyPressed(Keyboard::Add)) zoom -= 0.06f;
    // перемещение карты
    if (Keyboard::isKeyPressed(Keyboard::Left) || Mouse::getPosition().x < 5) {
        mapView.move(-6 * zoom, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) || Mouse::getPosition().x > window->getSize().x - 5) {
        mapView.move(6 * zoom, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Down) || Mouse::getPosition().y < 5) {
        mapView.move(0, -6 * zoom);
    }
    if (Keyboard::isKeyPressed(Keyboard::Up) || Mouse::getPosition().y > window->getSize().y - 5) {
        mapView.move(0, 6 * zoom);
    }
    // максимальный и минимальный зум
    if (zoom < 0.5) zoom = 0.5;
    if (zoom > minZoom) zoom = minZoom;
    // запрет на прокрутку за пределы карты по вертикали
    if (mapView.getCenter().y < windowHeight * zoom / 4)
        mapView.setCenter(mapView.getCenter().x, windowHeight * zoom / 4);
    if (mapView.getCenter().y > 0.25 * TILE_HEIGHT * (1 + 3 * MAP_HEIGHT) - windowHeight / 4. * zoom)
        mapView.setCenter(mapView.getCenter().x,
                          0.25f * TILE_HEIGHT * (1 + 3 * MAP_HEIGHT) - windowHeight / 4.f * zoom);
    // бесконечная прокрутка по горизонтали
    if (mapView.getCenter().x <= -windowWidth * zoom / 4)
        mapView.setCenter((TILE_WIDTH * (MAP_WIDTH)) - windowWidth / 4.f * zoom, mapView.getCenter().y);
    if (mapView.getCenter().x >= (TILE_WIDTH * (0.5 + MAP_WIDTH)) + windowWidth * zoom / 4.f)
        mapView.setCenter(windowWidth * zoom / 4.f + TILE_WIDTH * 0.5f, mapView.getCenter().y);
}


void MapScreen::draw() {
    // отрисовка карты
    window->setView(mapView);
    Vector2i lowerLeftTile = DrawableGrid::getTileByCoordinates(window->mapPixelToCoords(Vector2i(0, 0)));
    Vector2i upperRightTile = DrawableGrid::getTileByCoordinates(
            window->mapPixelToCoords(Vector2i(windowWidth, windowHeight)));
    drawableGrid->render(window, mapMode,
                         lowerLeftTile.x - 1, lowerLeftTile.y - 1, upperRightTile.x + 2, upperRightTile.y + 2);
    // отрисовка интерфейса
    window->setView(uiView);
    gui->render(window);
}

void MapScreen::zoomAtPoint(Vector2i point) {
    if (zoom < 0.5) zoom = 0.5;
    if (zoom > minZoom) zoom = minZoom;
    // установка mapView, чтобы убедиться что расчеты не будут проведены для другого view
    window->setView(mapView);
    Vector2 worldCoordinatesBeforeZoom = window->mapPixelToCoords(point);
    mapView.setSize(initialWidth * zoom, initialHeight * zoom);
    // зум
    window->setView(mapView);
    Vector2 worldCoordinatesAfterZoom = window->mapPixelToCoords(point);
    Vector2 diff = worldCoordinatesBeforeZoom - worldCoordinatesAfterZoom;
    mapView.move(diff);
    window->setView(mapView);
}