#pragma once

#include <json.hpp>
#include <fstream> // для считывания json-файла
#include "Type.h"

using Json = nlohmann::json;

class Tileset {
  public:
    static Tileset &get();

    Type *getType(const string &type);

    Tileset(Tileset const &) = delete;

    Tileset &operator=(Tileset const &) = delete;

  private:
    std::vector<Type *> tileset;

    Tileset();

    ~Tileset() = default;
};