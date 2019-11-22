#include "drawable_grid.h"

DrawableGrid::DrawableGrid() {
  grid_ = Generator().Generate();

  max_z_ = grid_->GetMaxZ();
  min_z_ = grid_->GetMinZ();

  Vector2f map_size = {R::kTileWidth * (0.5f + grid_->size_.x), 0.25f * R::kTileHeight * (3 * grid_->size_.y)};

  View view;
  view.setCenter(map_size / 2.f);
  view.setSize(map_size);

  center_ = new RenderTexture();
  center_->create(Texture::getMaximumSize() / 2, (Texture::getMaximumSize() / 2) / 300 * 190);
  center_->setView(view);

  UpdateTexture(MapMode::NORMAL);

  s_center_.setTexture(center_->getTexture());
  s_center_.scale(map_size.x / s_center_.getTexture()->getSize().x, map_size.y / s_center_.getTexture()->getSize().y);
  s_center_.setPosition(0, 0);

  s_right_.setTexture(center_->getTexture());
  s_right_.scale(map_size.x / s_right_.getTexture()->getSize().x, map_size.y / s_right_.getTexture()->getSize().y);
  s_right_.setPosition(map_size.x - 0.5f * R::kTileWidth, 0);

  s_left_.setTexture(center_->getTexture());
  s_left_.scale(map_size.x / s_left_.getTexture()->getSize().x, map_size.y / s_left_.getTexture()->getSize().y);
  s_left_.setPosition(-map_size.x + 0.5f * R::kTileWidth, 0);

  selected_tile_.setTexture(*AssetLoader::Get().GetTexture("selected_tile"));
  selected_tile_.scale(R::kTileWidth / selected_tile_.getTexture()->getSize().x,
                       R::kTileHeight / selected_tile_.getTexture()->getSize().y);
}

void DrawableGrid::RenderGridTexture(RenderTarget *target, MapMode mode, int x0, int x1) {
  if (prev_mode_ != mode) {
    UpdateTexture(mode);
    prev_mode_ = mode;
  }
  target->draw(s_center_);
  if (x1 > grid_->size_.x) target->draw(s_right_);
  if (x0 < 0) target->draw(s_left_);

  RenderSelectedTile(target, x0, x1);
}

void DrawableGrid::RenderVector(RenderTarget *target, MapMode mode, Vector2s lower_left, Vector2s upper_right) {
  if (lower_left.y < 0) lower_left.y = 0;
  if (upper_right.y > grid_->size_.y) upper_right.y = grid_->size_.y;
  if (lower_left.x < 0) {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = 0; j < upper_right.x; j++)
        RenderTile(target, mode, {j, i}, {j, i});
      for (uint16_t j = lower_left.x + grid_->size_.x; j < grid_->size_.x; j++)
        RenderTile(target, mode, {j, i}, {j - grid_->size_.x, i});
    }
  } else if (upper_right.x > grid_->size_.x) {
    upper_right.x = upper_right.x % grid_->size_.x;
    for (uint16_t i = lower_left.y; i < upper_right.y; i++) {
      for (uint16_t j = grid_->size_.x; j < upper_right.x + grid_->size_.x; j++)
        RenderTile(target, mode, Vector2u(j - grid_->size_.x, i), {j, i});
      for (uint16_t j = lower_left.x; j < grid_->size_.x; j++)
        RenderTile(target, mode, {j, i}, {j, i});
    }
  } else {
    for (uint16_t i = lower_left.y; i < upper_right.y; i++)
      for (uint16_t j = lower_left.x; j < upper_right.x; j++)
        RenderTile(target, mode, {j, i}, {j, i});
  }

  RenderSelectedTile(target, lower_left.x, upper_right.x);
}

void DrawableGrid::UpdateTexture(MapMode mode) {
  center_->clear(Color::Transparent);
  for (uint16_t i = 0; i < grid_->size_.x; i++) {
    for (uint16_t j = 0; j < grid_->size_.y; j++) {
      RenderTile(center_, mode, {i, j}, {i, j});
    }
  }
  center_->display();
}

void DrawableGrid::RenderSelectedTile(RenderTarget *target, int x0, int x1) {
  if (selected_.x >= 0 && selected_.y >= 0) {
    Vector2f tile_pos = {
        R::kTileWidth * (selected_.x + (selected_.y % 2 == 1 ? 0.5f : 0)),
        R::kTileHeight * (selected_.y - (selected_.y / 2) / 2.f - (selected_.y % 2 == 1 ? 0.25f : 0))
    };
    if (x0 < 0 && (selected_.x < 0 || selected_.x >= x1)) {
      selected_tile_.setPosition(tile_pos.x - R::kTileWidth * grid_->size_.x, tile_pos.y);
    } else if (x1 > grid_->size_.x && selected_.x < x1 % grid_->size_.x) {
      selected_tile_.setPosition(tile_pos.x + R::kTileWidth * grid_->size_.x, tile_pos.y);
    } else {
      selected_tile_.setPosition(tile_pos);
    }
    target->draw(selected_tile_);
  }
}

Vector2u DrawableGrid::UpdateSelection(Vector2f position) {
  selected_ = GetTileByCoords(position);
  // если клик на тайл на боковой карте - перенести его координаты на основную
  if (selected_.x > grid_->size_.x - 1) selected_.x -= grid_->size_.x;
  if (selected_.x < 0) selected_.x += grid_->size_.x;
  return Vector2u(selected_.x, selected_.y);
}

Vector2s DrawableGrid::GetTileByCoords(Vector2f coords) {
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

Tile *DrawableGrid::GetTile(Vector2u coords) const {
  return grid_->GetTile(coords);
}

void DrawableGrid::RenderTile(RenderTarget *target, MapMode mode, Vector2u coords, Vector2i pos) {
  float temp;
  Color color;
  Tile *tile = grid_->GetTile(coords);
  switch (mode) {
    case NORMAL:color = tile->GetType()->GetBaseColor(tile->GetLevel());
      break;
    case TEMPERATURE: // низкая температура - белый, высокая - красный
      temp = (float) (tile->GetTemperature() - G::GetMinTemp()) / (float) (G::GetMaxTemp() - G::GetMinTemp());
      color = Color(255, (1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case HEIGHT: // большая высота - белый, маленькая - синий
      temp = (float) (tile->GetZ() - min_z_) / (float) (max_z_ - min_z_ + 1);
      color = Color((1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case BIOMES:color = tile->GetType()->biome_color;
      break;
    case MINIMAP:
      if (tile->GetType()->archtype == "Water") {
        color = Color(179, 171, 128);
      } else {
        color = Color(108, 106, 68);
      }
      break;
    case MOISTURE: // высокая влажность - синий, низкая - беый
      color = Color((1 - tile->GetMoisture()) * 255, (1 - tile->GetMoisture()) * 255, 255, 255);
      break;
    case SELECTED:color = Color(0, 0, 0, 150);
      break;
  }
  RenderTileTriangles(target, color, pos);
}

void DrawableGrid::RenderTileTriangles(RenderTarget *target, Color color, Vector2i pos) {
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
  target->draw(shape);
}

Vector2<uint16_t> DrawableGrid::GetSize() const {
  return grid_->size_;
}
