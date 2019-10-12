#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <fstream> // для считывания json-файла

#include <json.hpp>

using namespace std;
using Json = nlohmann::json;

class R {
 public:
  static R &get();

  R(R const &) = delete;

  R &operator=(R const &) = delete;

  [[nodiscard]] uint16_t getUint(const string &name) const;

 private:
  map<string, uint16_t> unsigned_map;

  R();

  ~R() = default;

};
