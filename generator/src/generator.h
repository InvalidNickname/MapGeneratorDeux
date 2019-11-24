#ifndef MGD_GENERATOR_SRC_GENERATOR_H
#define MGD_GENERATOR_SRC_GENERATOR_H

#include "tile/tile_grid.h"
#include "utils/random.h"
#include "utils/perlin_noise.h"

/// @brief Основной класс генератора, создаёт карту
class Generator {
 public:
  /**
   * @brief Создаёт и возвращает сгенерированную карту
   * @return Сгенерированная карта TileGrid
  */
  TileGrid *Generate();

 private:
  TileGrid *grid_{nullptr}; ///< Созданная и возвращаемая карта
  uint16_t ocean_level_{0}; ///< Уровень моря
  uint16_t land_border_; ///< Верхняя и нижняя граница суши
  vector<vector<float>> factor_; ///< Веса для генерации река
  uint16_t river_length_; ///< Длина текущей генерируемой реки

  /// @brief Создаёт карту высот
  void RaiseTerrain();

  /// @brief Выравнивает карту высот
  void FlattenTerrain();

  /// @brief определение максимальной, минимальной высоты и уровня моря
  void FindZLimits();

  /// @brief Создаёт карту температур
  void SetTemperature();

  /// @brief Определяет все тайлы с высотой выше уровня моря как "суша" для последующего сглаживания границ континентов
  void SetLand();

  /// @brief Сглаживает границы континентов, убирает участи суши и воды размеров в 1 клетку
  void FlattenContinentBorders();

  /// @brief Устанавливает высоты (Level) гексов
  void SetTerrainLevel();

  /// @brief Создаёт карту влажности
  void SetMoisture();

  /// @brief Расставляет типы местности в соответствии с Tileset и tiles.json
  void SetTerrainFromTileset();

  /// @brief Создаёт реки
  void SetRivers();

  /**
   * @brief Рекурсивная функция для продления реки
   * @param pos Координаты гекса, в котором продолжается река
  */
  void ContinueRiver(Vector2u pos);

  /**
   * @brief Рекурсивная функция для удаления реки
   * @param pos Координаты гекса, в котором удаляется река
  */
  void DeleteRiver(Vector2u pos);

  /**
   * @brief Рекурсивное удаление гексов, имеющих только 2 соседей того же типа, вызывается в FlattenTerrain()
   * @param type Какой тип надо менять
   * @param change_to На какой тип надо менять
   * @param tile Тайл, тип которого меняется
  */
  void DeleteTilePaths(const string &type, const string &change_to, Tile *tile);

  /**
   * @brief Подсчитывает количество соседей заданного гекса с определённым типом
   * @param type Соседей с этим типом надо подсчитать
   * @param tile Гекс, соседей которого надо подсчитать
   * @return Количество соседей с заданным типом
   */
  uint8_t CountNeighboursWithType(const string &type, Tile *tile);
};

#endif
