#include <cmath>

struct MapParameters {
  public:
    constexpr static float TILE_HEIGHT = 80;
    constexpr static float TILE_WIDTH = 69.282032302755091741097853660235;

    const static int MAP_WIDTH = 300;
    const static int MAP_HEIGHT = 180;

    constexpr static int LAND_BORDER = (int) (0.07 * MAP_HEIGHT);

    const static int TEMPERATURE_MIN = -10;
    const static int TEMPERATURE_MAX = 50;
};