#ifndef MGD_GENERATOR_SRC_TILE_TYPE_TYPE_H
#define MGD_GENERATOR_SRC_TILE_TYPE_TYPE_H

#include <string>
#include <vector>
#include <utility>
#include <SFML/Graphics/Color.hpp>

#include "level.h"

using namespace std;
using namespace sf;

/// @brief Тип местности
struct Type {
 public:
  const string type_name; ///< Имя типа, используется как id
  const string archtype; ///< Архетип, для объединения нескольких типов в группы
  const Color biome_color; ///< Цвет этого типа на упрощенной карте
  // информация для генерации
  const bool above_sea_level; ///< Находится этот тип выше или ниже уровня моря
  const int priority; ///< Приоритет установки этого типа при генерации
  const pair<uint16_t, uint16_t> *temperature_range; ///< Интервал допустимый температур для этого типа
  const pair<float, float> *moisture_range; ///< Интервал допустимой влажности для этого типа
  const string neighbour; ///< Обязательный соседний тип

  /**
   * Конструктор типа
   * @param t Название типа
   * @param at Архетип
   * @param n Вектор имен типа, отображаемых пользователю. Количество имен должно быть равно количеству уровней в Level
   * @param bic Цвет типа на упрощенный карте
   * @param bac Вектор цветов типа на стандартной карте. Количество цветов должно быть равно количеству уровней в Level
   * @param asl Выше или ниже уровня моря находится тип
   * @param priority Приоритет установки при генерации
   * @param tr Интервал температур
   * @param mr Интервал влажности
   * @param neighbour Обязательный сосед
   */
  Type(string t, string at, vector<string> n, Color bic, vector<Color> bac, bool asl, int priority,
       pair<uint16_t, uint16_t> *tr, pair<float, float> *mr, const string &neighbour)
      : type_name(move(t)), archtype(move(at)), name(move(n)), biome_color(bic), base_color(move(bac)),
        above_sea_level(asl), priority(priority), temperature_range(tr), moisture_range(mr),
        neighbour(neighbour) {}

  /**
   * Возвращает имя типа для определённого уровня
   * @param level Уровень гекса
   * @return Имя типа для этого уровня
   */
  [[nodiscard]] string GetName(Level level) const;

  /**
   * Возвращает цвет типа для определённого уровня
   * @param level Уровень гекса
   * @return ЦВет типа для этого уровня
   */
  [[nodiscard]] Color GetBaseColor(Level level) const;

 private:
  const vector<Color> base_color; ///< Вектор цветов
  const vector<string> name; ///< Вктор имен типа
};

#endif