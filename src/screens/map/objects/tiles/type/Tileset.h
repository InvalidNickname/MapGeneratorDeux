#pragma once

#include <fstream> // для считывания json-файла

#include <json.hpp>

#include "utils/G.h"
#include "Type.h"

using Json = nlohmann::json;

class Tileset {
 public:
  static Tileset &get();

  [[nodiscard]] Type *getType(const string &type) const;

  [[nodiscard]] Type *getType(const uint16_t &index) const;

  [[nodiscard]] uint16_t getSize() const;

  Tileset(Tileset const &) = delete;

  Tileset &operator=(Tileset const &) = delete;

 private:
  std::vector<Type *> tileset;

  Tileset();

  ~Tileset() = default;
};