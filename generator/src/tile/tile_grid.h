#ifndef MGD_GENERATOR_SRC_TILE_TILE_GRID_H
#define MGD_GENERATOR_SRC_TILE_TILE_GRID_H

#include "tile.h"

using namespace std;

/// @brief Сетка гексов
class TileGrid {
 public:
  const Vector2<uint16_t> size_; ///< Размеры карты

  /**
   * Конструктор сетки карты
   * @param map_size Размер карты
   */
  explicit TileGrid(Vector2u map_size);

  /**
   * Возвращает гекс по указанным координатам
   * @param pos Координаты возвращаемого гекса
   * @return Tile по указанным координатам
   */
  [[nodiscard]] Tile *GetTile(Vector2u pos) const;

  /**
   * Возвращает соседа гекса по указанным координатам в укащанном направлении
   * @param direction Число от 0 до 6, направление на соседа
   * @param pos Координаты гекса, чьего соседа надо найти
   * @return Tile соседа, nullptr если такого соседа не существует (например при запросе соседа сверху у самого верхнего гекса)
   */
  [[nodiscard]] Tile *GetNeighbour(int direction, Vector2u pos) const;

  /**
   * Возвращает соседа указанного гекса в укащанном направлении
   * @param direction Число от 0 до 6, направление на соседа
   * @param tile Гекс, чьего соседа надо найти
   * @return Tile соседа, nullptr если такого соседа не существует (например при запросе соседа сверху у самого верхнего гекса)
   */
  [[nodiscard]] Tile *GetNeighbour(int direction, Tile *tile) const;

  /**
   * Возвращает максимальную высоту карты
   * @return Максимальная высота карты
   */
  [[nodiscard]] int GetMaxZ() const;

  /**
   * Устанавливание максимальную высоту карты
   * @param max_z Максимальная высота карты
   */
  void SetMaxZ(int max_z);

  /**
   * Возвращает минимальную высоту карты
   * @return Минимальная высота карты
   */
  [[nodiscard]] int GetMinZ() const;

  /**
   * Устанавливает минимальную высоту карты
   * @param min_z Минимальная высота карты
   */
  void SetMinZ(int min_z);

  /**
   * Отмечает, есть ли по этим координатам река
   * @param pos Координаты на карте
   * @param isRiver Есть река или нет
   */
  void SetRiver(Vector2u pos, bool isRiver);

  /**
   * Возвращает, есть ли по указанным координатам река
   * @param pos Координаты на карте
   * @return Есть ли река по этим координатам
   */
  [[nodiscard]] bool GetRiver(Vector2u pos) const;

 private:
  vector<vector<Tile *> *> *grid_; ///< Карта гексом
  vector<vector<bool> *> *river_map_; ///< Карта рек
  int max_z_{INT32_MIN}; ///< Максимальная высота карты
  int min_z_{INT32_MAX}; ///< Минимальная высота карты
};

#endif