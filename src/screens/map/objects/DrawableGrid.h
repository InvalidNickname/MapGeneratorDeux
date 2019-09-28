#include <screens/map/objects/tiles/TileGrid.h>
#include <screens/map/MapParameters.h>

class DrawableGrid {
  public:
    DrawableGrid();

    void render(RenderWindow *_window, int x0, int y0, int x1, int y1);

    Vector2i static getTileByCoordinates(Vector2f coords);

  private:
    TileGrid *tileGrid;
    int selectedX{-1}, selectedY{-1};

};