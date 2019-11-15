#include "DrawableGrid.h"

DrawableGrid::DrawableGrid() {
  tile_grid = Generator().generate();

  max_z = tile_grid->getMaxZ();
  min_z = tile_grid->getMinZ();

  Vector2f map_size = {R::kTileWidth * (0.5f + G::GetMapW()), 0.25f * R::kTileHeight * (3 * G::GetMapH())};

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
  s_right.setPosition(map_size.x - 0.5f * R::kTileWidth, 0);

  s_left.setTexture(center->getTexture());
  s_left.scale(map_size.x / s_left.getTexture()->getSize().x, map_size.y / s_left.getTexture()->getSize().y);
  s_left.setPosition(-map_size.x + 0.5f * R::kTileWidth, 0);

  selected_tile.setTexture(*AssetLoader::get().getTexture("selected_tile"));
  selected_tile.scale(R::kTileWidth / selected_tile.getTexture()->getSize().x,
                      R::kTileHeight / selected_tile.getTexture()->getSize().y);
}

void DrawableGrid::renderTexture(RenderTarget *_target, MapMode mode, int x0, int x1) {
  if (prev_mode != mode) {
    updateTexture(mode);
    prev_mode = mode;
  }
  _target->draw(s_center);
  if (x1 > G::GetMapW()) _target->draw(s_right);
  if (x0 < 0) _target->draw(s_left);

  renderSelectedTile(_target, x0, x1);
}

void DrawableGrid::renderVector(RenderTarget *_target, MapMode mode, Vector2s lower_left, Vector2s upper_right) {
  if (lower_left.y < 0) lower_left.y = 0;
  if (upper_right.y > G::GetMapH()) upper_right.y = G::GetMapH();
  if (lower_left.x < 0) {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = 0; j < upper_right.x; j++)
        renderTile(_target, mode, {j, i}, {j, i});
      for (uint16_t j = lower_left.x + G::GetMapW(); j < G::GetMapW(); j++)
        renderTile(_target, mode, {j, i}, {j - G::GetMapW(), i});
    }
  } else if (upper_right.x > G::GetMapW()) {
    upper_right.x = upper_right.x % G::GetMapW();
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = G::GetMapW(); j < upper_right.x + G::GetMapW(); j++)
        renderTile(_target, mode, Vector2u(j - G::GetMapW(), i), {j, i});
      for (uint16_t j = lower_left.x; j < G::GetMapW(); j++)
        renderTile(_target, mode, {j, i}, {j, i});
    }
  } else {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++)
      for (uint16_t j = lower_left.x; j < upper_right.x; j++)
        renderTile(_target, mode, {j, i}, {j, i});
  }

  renderSelectedTile(_target, lower_left.x, upper_right.x);
}

void DrawableGrid::updateTexture(MapMode mode) {
  center->clear(Color::Transparent);
  for (uint16_t i = 0; i < G::GetMapW(); i++) {
    for (uint16_t j = 0; j < G::GetMapH(); j++) {
      renderTile(center, mode, {i, j}, {i, j});
    }
  }
  center->display();
}

void DrawableGrid::renderSelectedTile(RenderTarget *_target, int x0, int x1) {
  if (selected.x >= 0 && selected.y >= 0) {
    Vector2f tile_pos = {
        R::kTileWidth * (selected.x + (selected.y % 2 == 1 ? 0.5f : 0)),
        R::kTileHeight * (selected.y - (selected.y / 2) / 2.f - (selected.y % 2 == 1 ? 0.25f : 0))
    };
    if (x0 < 0 && (selected.x < 0 || selected.x >= x1)) {
      selected_tile.setPosition(tile_pos.x - R::kTileWidth * G::GetMapW(), tile_pos.y);
    } else if (x1 > G::GetMapW() && selected.x < x1 % G::GetMapW()) {
      selected_tile.setPosition(tile_pos.x + R::kTileWidth * G::GetMapW(), tile_pos.y);
    } else {
      selected_tile.setPosition(tile_pos);
    }
    _target->draw(selected_tile);
  }
}

Vector2u DrawableGrid::updateSelection(Vector2f position) {
  selected = getTileByCoords(position);
  // если клик на тайл на боковой карте - перенести его координаты на основную
  if (selected.x > G::GetMapW() - 1) selected.x -= G::GetMapW();
  if (selected.x < 0) selected.x += G::GetMapW();
  return Vector2u(selected.x, selected.y);
}

Vector2s DrawableGrid::getTileByCoords(Vector2f coords) {
  // relative - относительное положение точки внутри тайла, единица длины - сторона тайла
  Vector2f temp = {coords.x / R::kTileWidth, coords.y / (R::kTileHeight / 2.f)};
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

void DrawableGrid::renderTile(RenderTarget *_target, MapMode mode, Vector2u coords, Vector2i pos) {
  float temp;
  Color color;
  Tile *tile = tile_grid->getTile(coords);
  switch (mode) {
    case NORMAL:color = tile->getType()->getBaseColor(tile->getLevel());
      break;
    case TEMPERATURE: // низкая температура - белый, высокая - красный
      temp = (float) (tile->getTemperature() - G::GetMinTemp()) / (float) (G::GetMaxTemp() - G::GetMinTemp());
      color = Color(255, (1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case HEIGHT: // большая высота - белый, маленькая - синий
      temp = (float) (tile->getZ() - min_z) / (float) (max_z - min_z + 1);
      color = Color((1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case BIOMES:color = tile->getType()->biome_color;
      break;
    case MINIMAP:
      if (tile->getType()->archtype == "Water") {
        color = Color(179, 171, 128);
      } else {
        color = Color(108, 106, 68);
      }
      break;
    case MOISTURE: // высокая влажность - синий, низкая - беый
      color = Color((1 - tile->getMoisture()) * 255, (1 - tile->getMoisture()) * 255, 255, 255);
      break;
    case SELECTED:color = Color(0, 0, 0, 150);
      break;
  }
  renderTileTriangles(_target, color, pos);
}

void DrawableGrid::renderTileTriangles(RenderTarget *_target, Color color, Vector2i pos) {
  Vector2f render_pos = {
      R::kTileWidth * ((float) pos.x + (pos.y % 2 == 1 ? 0.5f : 0)),
      R::kTileHeight * ((float) pos.y - (float) (pos.y / 2) / 2 - (pos.y % 2 == 1 ? 0.25f : 0))
  };
  auto shape = VertexArray(TriangleFan, 8);
  shape[0].position = Vector2f(render_pos.x + R::kTileWidth / 2, render_pos.y + R::kTileHeight / 2);
  shape[0].color = color;
  shape[1].position = Vector2f(render_pos.x + R::kTileWidth / 2, render_pos.y + R::kTileHeight);
  shape[1].color = color;
  shape[2].position = Vector2f(render_pos.x + R::kTileWidth, render_pos.y + R::kTileHeight * 3 / 4.f);
  shape[2].color = color;
  shape[3].position = Vector2f(render_pos.x + R::kTileWidth, render_pos.y + R::kTileHeight / 4.f);
  shape[3].color = color;
  shape[4].position = Vector2f(render_pos.x + R::kTileWidth / 2, render_pos.y);
  shape[4].color = color;
  shape[5].position = Vector2f(render_pos.x, render_pos.y + R::kTileHeight / 4.f);
  shape[5].color = color;
  shape[6].position = Vector2f(render_pos.x, render_pos.y + R::kTileHeight * 3 / 4.f);
  shape[6].color = color;
  shape[7].position = Vector2f(render_pos.x + R::kTileWidth / 2, render_pos.y + R::kTileHeight);
  shape[7].color = color;
  _target->draw(shape);
}