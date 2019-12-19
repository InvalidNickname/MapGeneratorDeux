#include "drawable_grid.h"

DrawableGrid::DrawableGrid() {
  grid_ = Generator().Generate();

  Vector2f map_size = {R::kTileWidth * (0.5f + grid_->size_.x), 0.25f * R::kTileHeight * (3 * grid_->size_.y)};

  center_ = new RenderTexture();
  center_->create(Texture::getMaximumSize() / 2, (Texture::getMaximumSize() / 2) / 300 * 190);
  center_->setView({map_size / 2.f, map_size});

  UpdateTexture(MapMode::NORMAL);

  s_center_.setTexture(center_->getTexture());
  s_center_.scale(map_size.x / s_center_.getTexture()->getSize().x, map_size.y / s_center_.getTexture()->getSize().y);
  s_center_.setPosition(0, 0);

  s_right_.setTexture(center_->getTexture());
  s_right_.scale(s_center_.getScale());
  s_right_.setPosition(map_size.x - 0.5f * R::kTileWidth, 0);

  s_left_.setTexture(center_->getTexture());
  s_left_.scale(s_center_.getScale());
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

Vector2u DrawableGrid::UpdateSelection(Vector2f position) {
  selected_ = GetTileByCoords(position);
  // если клик на тайл на боковой карте - перенести его координаты на основную
  if (selected_.x > grid_->size_.x - 1) selected_.x -= grid_->size_.x;
  if (selected_.x < 0) selected_.x += grid_->size_.x;
  UpdateTexture(prev_mode_);
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
    tile.y = (uint16_t) floor(temp.y / 1.5);
  else {
    // в верхней или нижней части гекса
    // четный ряд
    if (fmod(temp.y, 1) > 0.5 && fmod(temp.y, 1) < 1) {
      if (relative.x < 0.5) {
        if (relative.y / relative.x < 1)
          tile.y = (uint16_t) floor(temp.y / 1.5) - 1u;
        else tile.y = (uint16_t) floor(temp.y / 1.5);
      } else {
        if (relative.y < 1 - relative.x)
          tile.y = (uint16_t) floor(temp.y / 1.5) - 1u;
        else tile.y = (uint16_t) floor(temp.y / 1.5);
      }
    } else { // нечетный ряд, есть смещение гексов
      if (relative.y < abs(relative.x - 0.5))
        tile.y = (uint16_t) floor(temp.y / 1.5) - 1u;
      else tile.y = (uint16_t) floor(temp.y / 1.5);
    }
  }

  tile.x = (uint16_t) floor(temp.x - (tile.y % 2 == 0 ? 0 : 0.5));

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
      temp = (float) (tile->GetZ() - grid_->GetMinZ()) / (float) (grid_->GetMaxZ() - grid_->GetMinZ() + 1);
      color = Color((1 - temp) * 255, (1 - temp) * 255, 255);
      break;
    case BIOMES:color = tile->GetType()->biome_color;
      break;
    case MINIMAP:
      if (!tile->GetType()->above_sea_level) {
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
  Vector2f render_pos = {
      R::kTileWidth * (pos.x + (fmod(pos.y, 2) == 1 ? 0.5f : 0)),
      R::kTileHeight * (pos.y - (float) (pos.y / 2) / 2 - (fmod(pos.y, 2) == 1 ? 0.25f : 0))
  };
  RenderTileTriangles(target, color, render_pos);
  if (mode == NORMAL) RenderRiver(target, coords, render_pos);
  if (coords.x == selected_.x && coords.y == selected_.y) {
    selected_tile_.setPosition(render_pos);
    target->draw(selected_tile_);
  }
}

void DrawableGrid::RenderTileTriangles(RenderTarget *target, Color color, Vector2f pos) {
  auto shape = VertexArray(TriangleFan, 8);
  shape[0].position = Vector2f(pos.x + R::kTileWidth / 2, pos.y + R::kTileHeight / 2);
  shape[0].color = color;
  shape[1].position = Vector2f(pos.x + R::kTileWidth / 2, pos.y + R::kTileHeight);
  shape[1].color = color;
  shape[2].position = Vector2f(pos.x + R::kTileWidth, pos.y + R::kTileHeight * 3 / 4.f);
  shape[2].color = color;
  shape[3].position = Vector2f(pos.x + R::kTileWidth, pos.y + R::kTileHeight / 4.f);
  shape[3].color = color;
  shape[4].position = Vector2f(pos.x + R::kTileWidth / 2, pos.y);
  shape[4].color = color;
  shape[5].position = Vector2f(pos.x, pos.y + R::kTileHeight / 4.f);
  shape[5].color = color;
  shape[6].position = Vector2f(pos.x, pos.y + R::kTileHeight * 3 / 4.f);
  shape[6].color = color;
  shape[7].position = Vector2f(pos.x + R::kTileWidth / 2, pos.y + R::kTileHeight);
  shape[7].color = color;
  target->draw(shape);
}

Vector2<uint16_t> DrawableGrid::GetSize() const {
  return grid_->size_;
}

void DrawableGrid::RenderRiver(RenderTarget *target, Vector2u coords, Vector2f pos) {
  if (grid_->GetRiver(coords)) {
    auto river = VertexArray(Quads, 4);
    river[0].position = pos;
    river[1].position = {pos.x + R::kTileWidth, pos.y};
    river[2].position = {pos.x + R::kTileWidth, pos.y + R::kTileHeight};
    river[3].position = {pos.x, pos.y + R::kTileHeight};
    // все текстуры рек должны быть одинаковыми по размеру, так то пофиг какую брать
    Vector2u tex_size = AssetLoader::Get().GetTexture("river_end")->getSize();
    river[3].texCoords = Vector2f(0.f, 0.f);
    river[2].texCoords = Vector2f((float) tex_size.x, 0.f);
    river[1].texCoords = Vector2f((float) tex_size.x, (float) tex_size.y);
    river[0].texCoords = Vector2f(0.f, (float) tex_size.y);
    Vector2f rot_center = {pos.x + R::kTileWidth / 2.f, pos.y + R::kTileHeight / 2.f};

    uint8_t from_dir{0}, to_dir{0};
    uint8_t dirs = 0;
    for (uint8_t i = 0; i < 6; ++i) {
      Vector2u n_pos = grid_->GetNeighbour(i, coords)->pos_;
      if (grid_->GetRiver(n_pos) && dirs == 0) {
        from_dir = i;
        dirs++;
      } else if (grid_->GetRiver(n_pos)) {
        to_dir = i;
        dirs++;
        break;
      }
    }
    // если это конец реки, она впадает в океан
    if (dirs == 1) {
      for (uint8_t i = 0; i < 6; ++i) {
        Vector2u n_pos = grid_->GetNeighbour(i, coords)->pos_;
        if (!grid_->GetTile(n_pos)->GetType()->above_sea_level) {
          to_dir = i;
          dirs++;
          break;
        }
      }
    }
    RenderStates states;
    if (dirs == 1) {
      states.texture = AssetLoader::Get().GetTexture("river_end");
      states.transform.rotate(GetRotation(from_dir), rot_center);
      target->draw(river, states);
    } else if (abs(from_dir - to_dir) == 2 || abs(from_dir - to_dir) == 4) {
      int16_t rotation = GetRotation(from_dir);
      if ((from_dir == 0 && to_dir == 2)
          || (from_dir == 1 && to_dir == 3)
          || (from_dir == 2 && to_dir == 4)
          || (from_dir == 3 && to_dir == 5)
          || (from_dir == 4 && to_dir == 0)
          || (from_dir == 5 && to_dir == 1)) {
        rotation -= 120;
      }
      states.texture = AssetLoader::Get().GetTexture("river_2");
      states.transform.rotate(rotation, rot_center);
      target->draw(river, states);
    } else {
      states.texture = AssetLoader::Get().GetTexture("river_straight");
      states.transform.rotate(GetRotation(from_dir), rot_center);
      target->draw(river, states);
    }
  }
}

uint16_t DrawableGrid::GetRotation(uint8_t direction) {
  switch (direction) {
    case 0:return 180;
    case 1:return 120;
    case 2:return 60;
    case 3:return 0;
    case 4:return 300;
    case 5:return 240;
    default:return 0;
  }
}