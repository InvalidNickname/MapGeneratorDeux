#include "DrawableGrid.h"

DrawableGrid::DrawableGrid() {
  tile_grid = Generator().generate();

  max_z = tile_grid->getMaxZ();
  min_z = tile_grid->getMinZ();

  float height = 0.25f * TILE_HEIGHT * (3 * MAP_HEIGHT);
  float width = TILE_WIDTH * (0.5f + MAP_WIDTH);

  View view;
  view.setCenter(width / 2, height / 2);
  view.setSize(width, height);

  center = new RenderTexture();
  center->create(Texture::getMaximumSize() / 2, (Texture::getMaximumSize() / 2) / 300 * 190);
  center->setView(view);

  updateTexture(MapMode::NORMAL);

  s_center.setTexture(center->getTexture());
  s_center.scale(width / s_center.getTexture()->getSize().x, height / s_center.getTexture()->getSize().y);
  s_center.setPosition(0, 0);

  s_right.setTexture(center->getTexture());
  s_right.scale(width / s_right.getTexture()->getSize().x, height / s_right.getTexture()->getSize().y);
  s_right.setPosition(width - 0.5f * TILE_WIDTH, 0);

  s_left.setTexture(center->getTexture());
  s_left.scale(width / s_left.getTexture()->getSize().x, height / s_left.getTexture()->getSize().y);
  s_left.setPosition(-width + 0.5f * TILE_WIDTH, 0);

  selected_tile.setTexture(*AssetLoader::get().getTexture("selected_tile"));
  selected_tile.scale(TILE_WIDTH / selected_tile.getTexture()->getSize().x,
                      TILE_HEIGHT / selected_tile.getTexture()->getSize().y);
}

void DrawableGrid::renderTexture(RenderTarget *_target, MapMode mode, int x0, int x1) {
  if (prev_mode != mode) {
    updateTexture(mode);
    prev_mode = mode;
  }
  _target->draw(s_center);
  if (x1 > MAP_WIDTH) _target->draw(s_right);
  if (x0 < 0) _target->draw(s_left);

  renderSelectedTile(_target, x0, x1);
}

void DrawableGrid::renderVector(RenderTarget *_target, MapMode mode, Vector2s lower_left, Vector2s upper_right) {
  if (lower_left.y < 0) lower_left.y = 0;
  if (upper_right.y > MAP_HEIGHT) upper_right.y = MAP_HEIGHT;
  if (lower_left.x < 0) {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = 0; j < upper_right.x; j++)
        tile_grid->getTile(j, i)->render(_target, mode, j, i, max_z, min_z);
      for (uint16_t j = lower_left.x + MAP_WIDTH; j < MAP_WIDTH; j++)
        tile_grid->getTile(j, i)->render(_target, mode, j - MAP_WIDTH, i, max_z, min_z);
    }
  } else if (upper_right.x > MAP_WIDTH) {
    upper_right.x = upper_right.x % MAP_WIDTH;
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = MAP_WIDTH; j < upper_right.x + MAP_WIDTH; j++)
        tile_grid->getTile(j - MAP_WIDTH, i)->render(_target, mode, j, i, max_z, min_z);
      for (uint16_t j = lower_left.x; j < MAP_WIDTH; j++)
        tile_grid->getTile(j, i)->render(_target, mode, j, i, max_z, min_z);
    }
  } else {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++)
      for (uint16_t j = lower_left.x; j < upper_right.x; j++)
        tile_grid->getTile(j, i)->render(_target, mode, j, i, max_z, min_z);
  }

  renderSelectedTile(_target, lower_left.x, upper_right.x);
}

void DrawableGrid::updateTexture(MapMode mode) {
  center->clear(Color::Transparent);
  for (uint16_t i = 0; i < MAP_WIDTH; i++) {
    for (uint16_t j = 0; j < MAP_HEIGHT; j++) {
      tile_grid->getTile(i, j)->render(center, mode, i, j, max_z, min_z);
    }
  }
  center->display();
}

void DrawableGrid::renderSelectedTile(RenderTarget *_target, int x0, int x1) {
  if (selected.x >= 0 && selected.y >= 0) {
    float tile_y = TILE_HEIGHT * (selected.y - (selected.y / 2) / 2.f - (selected.y % 2 == 1 ? 0.25f : 0));
    float tile_x = TILE_WIDTH * (selected.x + (selected.y % 2 == 1 ? 0.5f : 0));
    if (x0 < 0 && (selected.x < 0 || selected.x >= x1)) {
      selected_tile.setPosition(tile_x - TILE_WIDTH * MAP_WIDTH, tile_y);
    } else if (x1 > MAP_WIDTH && selected.x < x1 % MAP_WIDTH) {
      selected_tile.setPosition(tile_x + TILE_WIDTH * MAP_WIDTH, tile_y);
    } else {
      selected_tile.setPosition(tile_x, tile_y);
    }
    _target->draw(selected_tile);
  }
}

Vector2s DrawableGrid::updateSelection(Vector2f position) {
  selected = getTileByCoordinates(position);
  // если клик на тайл на боковой карте - перенести его координаты на основную
  if (selected.x > MAP_WIDTH - 1) selected.x = selected.x - MAP_WIDTH;
  if (selected.x < 0) selected.x = MAP_WIDTH + selected.x;
  return selected;
}

Vector2s DrawableGrid::getTileByCoordinates(Vector2f coords) {
  // relative - положение точки внутри тайла, единица длины - сторона тайла

  float temp_y = coords.y / (TILE_HEIGHT / 2.f);
  float relative_y = fmod(temp_y, 1.5f);
  int16_t tile_y;

  float temp_x = coords.x / (TILE_WIDTH);
  if (temp_x < 0.5) temp_x -= 1;
  float relative_x = fmod(temp_x, 1.f);
  if (relative_x < 0) relative_x++;
  int16_t tile_x;

  if (relative_y >= 0.5 && relative_y < 1.5)
    // точка нахожится в центральной части гекса
    tile_y = (int16_t) (temp_y / 1.5);
  else {
    // в верхней или нижней части гекса
    // четный ряд
    if (fmod(temp_y, 1) > 0.5 && fmod(temp_y, 1) < 1) {
      if (relative_x < 0.5) {
        if (relative_y / relative_x < 1)
          tile_y = (int16_t) (temp_y / 1.5) - 1;
        else tile_y = (int16_t) (temp_y / 1.5);
      } else {
        if (relative_y < 1 - relative_x)
          tile_y = (int16_t) (temp_y / 1.5) - 1;
        else tile_y = (int16_t) (temp_y / 1.5);
      }
    } else { // нечетный ряд, есть смещение гексов
      if (relative_x < 0.5) {
        if (relative_y < 0.5 - relative_x)
          tile_y = (int16_t) (temp_y / 1.5) - 1;
        else tile_y = (int16_t) (temp_y / 1.5);
      } else {
        if (relative_y / (relative_x - 0.5) < 1)
          tile_y = (int16_t) (temp_y / 1.5) - 1;
        else tile_y = (int16_t) (temp_y / 1.5);
      }
    }
  }

  tile_x = (int16_t) (temp_x - (tile_y % 2 == 0 ? 0 : 0.5));

  return {tile_x, tile_y};
}

Tile *DrawableGrid::getTile(Vector2s coords) const {
  return tile_grid->getTile(coords.x, coords.y);
}
