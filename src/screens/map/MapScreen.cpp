#include "MapScreen.h"

void MapScreen::draw() {
    Vector2i lowerLeftTile = DrawableGrid::getTileByCoordinates(window->mapPixelToCoords(Vector2i(0, 0)));
    Vector2i upperRightTile = DrawableGrid::getTileByCoordinates(
            window->mapPixelToCoords(Vector2i(windowWidth, windowHeight)));
    drawableGrid->render(window, mapMode,
                         lowerLeftTile.x - 1, lowerLeftTile.y - 1, upperRightTile.x + 2, upperRightTile.y + 2);
}

void MapScreen::doAction() {
    handleInput();
    view.setSize(initialWidth * zoom, initialHeight * zoom);
    window->setView(view);
}

MapScreen::MapScreen(RenderWindow *renderWindow) : Screen(renderWindow) {
    // размеры экрана
    windowHeight = window->getSize().y;
    windowWidth = window->getSize().x;
    // создание сетки для отрисовки
    drawableGrid = new DrawableGrid();
    // начальные размеры экрана
    initialHeight = windowHeight / 2.f;
    initialWidth = windowWidth / 2.f;
    // установка камеры
    view.setSize(initialWidth, initialHeight);
    float camX = TILE_WIDTH * (0.5f + MAP_WIDTH) / 2;
    float camY = 0.125f * TILE_HEIGHT * (1 + 3 * MAP_HEIGHT);
    view.setCenter(camX, camY);
    // минимвльный зум - сетка полностью помещается на экран по высоте
    minZoom = camY * 2 / initialHeight;
    view.zoom(minZoom);
    zoom = minZoom;
    window->setView(view);
}

void MapScreen::handleInput() {
    Event event{};
    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.delta < 0) zoom += 0.4f;
                else zoom -= 0.4f;
                break;
        }
    }
    // смена режимов карты
    if (isKeyPressed(Keyboard::Q)) mapMode = MapMode::NORMAL;
    else if (isKeyPressed(Keyboard::T)) mapMode = MapMode::TEMPERATURE;
    else if (isKeyPressed(Keyboard::H)) mapMode = MapMode::HEIGHT;
    else if (isKeyPressed(Keyboard::B)) mapMode = MapMode::BIOMES;
    // отдаление
    if (isKeyPressed(Keyboard::Subtract)) zoom += 0.06f;
    // приближение
    if (isKeyPressed(Keyboard::Add)) zoom -= 0.06f;
    // перемещение карты
    if (isKeyPressed(Keyboard::Left) || Mouse::getPosition().x < 5) view.move(-6 * zoom, 0);
    if (isKeyPressed(Keyboard::Right) || Mouse::getPosition().x > window->getSize().x - 5) view.move(6 * zoom, 0);
    if (isKeyPressed(Keyboard::Down) || Mouse::getPosition().y < 5) view.move(0, -6 * zoom);
    if (isKeyPressed(Keyboard::Up) || Mouse::getPosition().y > window->getSize().y - 5) view.move(0, 6 * zoom);
    // максимальный и минимальный зум
    if (zoom < 0.5) zoom = 0.5;
    if (zoom > minZoom) zoom = minZoom;
    // запрет на прокрутку за пределы карты по вертикали
    if (view.getCenter().y < windowHeight * zoom / 4) view.setCenter(view.getCenter().x, windowHeight * zoom / 4);
    if (view.getCenter().y > 0.25 * TILE_HEIGHT * (1 + 3 * MAP_HEIGHT) - windowHeight / 4. * zoom)
        view.setCenter(view.getCenter().x, 0.25f * TILE_HEIGHT * (1 + 3 * MAP_HEIGHT) - windowHeight / 4.f * zoom);
    // бесконечная прокрутка по горизонтали
    if (view.getCenter().x <= -windowWidth * zoom / 4)
        view.setCenter((TILE_WIDTH * (MAP_WIDTH)) - windowWidth / 4.f * zoom, view.getCenter().y);
    if (view.getCenter().x >= (TILE_WIDTH * (0.5 + MAP_WIDTH)) + windowWidth * zoom / 4.f)
        view.setCenter(windowWidth * zoom / 4.f + TILE_WIDTH * 0.5f, view.getCenter().y);
}

// чисто для сокращения с Keyboard::isKeyPressed() до isKeyPressed()
bool MapScreen::isKeyPressed(Keyboard::Key key) {
    return Keyboard::isKeyPressed(key);
}
