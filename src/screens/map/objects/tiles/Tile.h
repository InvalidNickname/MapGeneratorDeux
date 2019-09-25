#include "Type.h"
#include <screens/map/MapParameters.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Tile {
  private:
    const int x, y;
    int z;
    float latitude, longitude;
    float tileX, tileY;
    float temperature;
    Type type;
  public:
    Tile(int x, int y);

    void render(RenderWindow *_window, int _x, int _y);

    float getLatitude();

    float getLongitude();

    int getX();

    int getY();

    int getZ();

    Type getType();

  private:
    void drawTile(RenderWindow *_window);
};