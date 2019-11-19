#ifndef MGD_GENERATOR_SRC_TILE_TYPE_TILESET_H
#define MGD_GENERATOR_SRC_TILE_TYPE_TILESET_H

#include <fstream> // для считывания json-файла

#include <json.hpp>

#include "utils/g.h"
#include "type.h"

using Json = nlohmann::json;

class Tileset {
 public:
  static Tileset &Get();

  [[nodiscard]] Type *GetType(const string &type) const;

  [[nodiscard]] Type *GetType(const uint16_t &index) const;

  [[nodiscard]] uint16_t GetSize() const;

  Tileset(Tileset const &) = delete;

  Tileset &operator=(Tileset const &) = delete;

 private:
  std::vector<Type *> tileset_;

  Tileset();

  ~Tileset() = default;
};

#endif