#ifndef MGD_GENERATOR_SRC_TILE_TYPE_TILESET_H
#define MGD_GENERATOR_SRC_TILE_TYPE_TILESET_H

#include <fstream> // для считывания json-файла

#include <json.hpp>

#include "utils/g.h"
#include "type.h"

using Json = nlohmann::json;

/// @brief Набор типов, успользуемых при генерации
class Tileset {
 public:
  static Tileset &Get();

  /**
   * Возвращает тип с указанным названием
   * @param type Название типа
   * @return Тип с указанным названием
   */
  [[nodiscard]] Type *GetType(const string &type) const;

  /**
   * Возвращает тип по указанному индексу
   * @param index Индекс типа
   * @return Тип по указанному индексу
   */
  [[nodiscard]] Type *GetType(const uint16_t &index) const;

  /**
   * Возвращает размер тайлсета
   * @return Размер тайлсета
   */
  [[nodiscard]] uint16_t GetSize() const;

  Tileset(Tileset const &) = delete;

  Tileset &operator=(Tileset const &) = delete;

 private:
  std::vector<Type *> tileset_; ///< Вектор всех типов, загруженных из tiles.json и используемых при генерации

  Tileset();

  ~Tileset() = default;
};

#endif