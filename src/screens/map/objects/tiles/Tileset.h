#pragma once

class Tileset {
  public:
    static Tileset &get();

    Tileset(Tileset const &) = delete;

    Tileset &operator=(Tileset const &) = delete;

  private:
    Tileset() = default;

    ~Tileset() = default;
};