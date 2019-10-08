#pragma once

#include <fstream> // для считывания json-файла

#include <json.hpp>

#include "Type.h"

using Json = nlohmann::json;

class Tileset {
  public:
    static Tileset &get();

    Type *getType(const string &type);

    Type *getType(const uint16_t &index);

    uint16_t getSize();

    Tileset(Tileset const &) = delete;

    Tileset &operator=(Tileset const &) = delete;

  private:
    std::vector<Type *> tileset;

    Tileset();

    ~Tileset() = default;
};