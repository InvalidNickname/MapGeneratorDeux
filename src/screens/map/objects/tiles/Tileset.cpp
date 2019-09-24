#include "Tileset.h"

Tileset &Tileset::get() {
    static Tileset s;
    return s;
}
