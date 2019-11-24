#ifndef MGD_GENERATOR_SRC_TILE_TILE_H
#define MGD_GENERATOR_SRC_TILE_TILE_H

#include <SFML/System.hpp>

#include "tile/type/tileset.h"

/// @brief Гекс
class Tile {
 public:
  const Vector2u pos_; ///< Координаты гекса на карте
  const float latitude_; ///< Широта гекса
  const float longitude_; ///< Долгота гекса

  /**
   * Конструктор гекса
   * @param pos Координаты гекса на карте
   */
  explicit Tile(Vector2u pos);

  /**
   * Возвращает высоту гекса
   * @return Высота гекса
   */
  [[nodiscard]] uint16_t GetZ() const;

  /**
   * Возвращает тип (Type) гекса
   * @return Тип гекса
   */
  [[nodiscard]] Type *GetType() const;

  /**
   * Устанавливает уровень гекса
   * @param level Уровень гекса
   */
  void SetLevel(Level level);

  /**
   * Устанавливает тип гекса
   * @param type Тип гекса
   */
  void SetType(const string &type);

  /**
   * Увеличивает высоту гекса
   * @param z Изменение высоты
   */
  void IncreaseZ(int z);

  /**
   * Устанавливает высоту гекса
   * @param z Новая высота гекса
   */
  void SetZ(uint16_t z);

  /**
   * Возвращает температуру гекса
   * @return Температура гекса
   */
  [[nodiscard]] uint16_t GetTemperature() const;

  /**
   * Устанавливает температуру гекса
   * @param temperature Температура гекса
   */
  void SetTemperature(uint16_t temperature);

  /**
   * Возвращает влажность гекса
   * @return Влажность гекса
   */
  [[nodiscard]] float GetMoisture() const;

  /**
   * Устанавливает влажность гекса
   * @param moisture Влажность гекса
   */
  void SetMoisture(float moisture);

  /**
   * Возвращает уровень гекса
   * @return Уровень гекса
   */
  [[nodiscard]] Level GetLevel() const;

 private:
  uint16_t z_{0}; ///< Высота гекса
  float moisture_{0}; ///< Влажность гекса
  uint16_t temperature_{0}; ///< Температура гекса
  Type *type_{nullptr}; ///< Тип местности гекса
  Level level_{Level::NO}; ///< Уровень гекса
};

#endif