#include "DrawableGrid.h"

DrawableGrid::DrawableGrid() {
  tile_grid = Generator().generate();

  max_z = tile_grid->getMaxZ();
  min_z = tile_grid->getMinZ();

  Vector2f map_size = {G::TILE_WIDTH * (0.5f + G::getMapW()), 0.25f * G::TILE_HEIGHT * (3 * G::getMapH())};

  View view;
  view.setCenter(map_size / 2.f);
  view.setSize(map_size);

  center = new RenderTexture();
  center->create(Texture::getMaximumSize() / 2, (Texture::getMaximumSize() / 2) / 300 * 190);
  center->setView(view);

  updateTexture(MapMode::NORMAL);

  s_center.setTexture(center->getTexture());
  s_center.scale(map_size.x / s_center.getTexture()->getSize().x, map_size.y / s_center.getTexture()->getSize().y);
  s_center.setPosition(0, 0);

  s_right.setTexture(center->getTexture());
  s_right.scale(map_size.x / s_right.getTexture()->getSize().x, map_size.y / s_right.getTexture()->getSize().y);
  s_right.setPosition(map_size.x - 0.5f * G::TILE_WIDTH, 0);

  s_left.setTexture(center->getTexture());
  s_left.scale(map_size.x / s_left.getTexture()->getSize().x, map_size.y / s_left.getTexture()->getSize().y);
  s_left.setPosition(-map_size.x + 0.5f * G::TILE_WIDTH, 0);

  selected_tile.setTexture(*AssetLoader::get().getTexture("selected_tile"));
  selected_tile.scale(G::TILE_WIDTH / selected_tile.getTexture()->getSize().x,
                      G::TILE_HEIGHT / selected_tile.getTexture()->getSize().y);
}

void DrawableGrid::renderTexture(RenderTarget *_target, MapMode mode, int x0, int x1) {
  if (prev_mode != mode) {
    updateTexture(mode);
    prev_mode = mode;
  }
  _target->draw(s_center);
  if (x1 > G::getMapW()) _target->draw(s_right);
  if (x0 < 0) _target->draw(s_left);

  renderSelectedTile(_target, x0, x1);
}

void DrawableGrid::renderVector(RenderTarget *_target, MapMode mode, Vector2s lower_left, Vector2s upper_right) {
  if (lower_left.y < 0) lower_left.y = 0;
  if (upper_right.y > G::getMapH()) upper_right.y = G::getMapH();
  if (lower_left.x < 0) {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = 0; j < upper_right.x; j++)
        tile_grid->getTile({j, i})->render(_target, mode, {j, i}, max_z, min_z);
      for (uint16_t j = lower_left.x + G::getMapW(); j < G::getMapW(); j++)
        tile_grid->getTile({j, i})->render(_target, mode, {j - G::getMapW(), i}, max_z, min_z);
    }
  } else if (upper_right.x > G::getMapW()) {
    upper_right.x = upper_right.x % G::getMapW();
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = G::getMapW(); j < upper_right.x + G::getMapW(); j++)
        tile_grid->getTile(Vector2u(j - G::getMapW(), i))->render(_target, mode, {j, i}, max_z, min_z);
      for (uint16_t j = lower_left.x; j < G::getMapW(); j++)
        tile_grid->getTile({j, i})->render(_target, mode, {j, i}, max_z, min_z);
    }
  } else {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++)
      for (uint16_t j = lower_left.x; j < upper_right.x; j++)
        tile_grid->getTile({j, i})->render(_target, mode, {j, i}, max_z, min_z);
  }

  renderSelectedTile(_target, lower_left.x, upper_right.x);
}

void DrawableGrid::updateTexture(MapMode mode) {
  center->clear(Color::Transparent);
  for (uint16_t i = 0; i < G::getMapW(); i++) {
    for (uint16_t j = 0; j < G::getMapH(); j++) {
      tile_grid->getTile({i, j})->render(center, mode, {i, j}, max_z, min_z);
    }
  }
  center->display();
}

void DrawableGrid::renderSelectedTile(RenderTarget *_target, int x0, int x1) {
  if (selected.x >= 0 && selected.y >= 0) {
    Vector2f tile_pos = {
        G::TILE_WIDTH * (selected.x + (selected.y % 2 == 1 ? 0.5f : 0)),
        G::TILE_HEIGHT * (selected.y - (selected.y / 2) / 2.f - (selected.y % 2 == 1 ? 0.25f : 0))
    };
    if (x0 < 0 && (selected.x < 0 || selected.x >= x1)) {
      selected_tile.setPosition(tile_pos.x - G::TILE_WIDTH * G::getMapW(), tile_pos.y);
    } else if (x1 > G::getMapW() && selected.x < x1 % G::getMapW()) {
      selected_tile.setPosition(tile_pos.x + G::TILE_WIDTH * G::getMapW(), tile_pos.y);
    } else {
      selected_tile.setPosition(tile_pos);
    }
    _target->draw(selected_tile);
  }
}

Vector2u DrawableGrid::updateSelection(Vector2f position) {
  selected = getTileByCoords(position);
  // если клик на тайл на боковой карте - перенести его координаты на основную
  if (selected.x > G::getMapW() - 1) selected.x -= G::getMapW();
  if (selected.x < 0) selected.x += G::getMapW();
  return Vector2u(selected.x, selected.y);
}

Vector2s DrawableGrid::getTileByCoords(Vector2f coords) {
  // relative - относительное положение точки внутри тайла, единица длины - сторона тайла
  Vector2f temp = {coords.x / G::TILE_WIDTH, coords.y / (G::TILE_HEIGHT / 2.f)};
  if (temp.x < 0.5) temp.x -= 1;
  Vector2f relative = {fmod(temp.x, 1.f), fmod(temp.y, 1.5f)};
  if (relative.x < 0) relative.x++;

  Vector2s tile;
  if (relative.y >= 0.5 && relative.y < 1.5)
    // точка нахожится в центральной части гекса
    tile.y = floor(temp.y / 1.5);
  else {
    // в верхней или нижней части гекса
    // четный ряд
    if (fmod(temp.y, 1) > 0.5 && fmod(temp.y, 1) < 1) {
      if (relative.x < 0.5) {
        if (relative.y / relative.x < 1)
          tile.y = floor(temp.y / 1.5) - 1;
        else tile.y = floor(temp.y / 1.5);
      } else {
        if (relative.y < 1 - relative.x)
          tile.y = floor(temp.y / 1.5) - 1;
        else tile.y = floor(temp.y / 1.5);
      }
    } else { // нечетный ряд, есть смещение гексов
      if (relative.y < abs(relative.x - 0.5))
        tile.y = floor(temp.y / 1.5) - 1;
      else tile.y = floor(temp.y / 1.5);
    }
  }

  tile.x = floor(temp.x - (tile.y % 2 == 0 ? 0 : 0.5));

  return tile;
}

Tile *DrawableGrid::getTile(Vector2u coords) const {
  return tile_grid->getTile(coords);
}
