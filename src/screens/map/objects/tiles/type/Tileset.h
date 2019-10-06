#pragma once

#include <fstream> // для считывания json-файла

#include <json.hpp>

#include "Type.h"

using Json = nlohmann::json;

class Tileset {
  public:
    static Tileset &get();

    Type *getType(const string &type);

    Type *getType(const int &index);

    int getSize();

    Tileset(Tileset const &) = delete;

    Tileset &operator=(Tileset const &) = delete;

  private:
    std::vector<Type *> tileset;

    Tileset();

    ~Tileset() = default;
};