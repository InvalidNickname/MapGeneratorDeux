#include <map>

#include <utils/AssetLoader.h>
#include "UIDrawable.h"

class GUI {
 public:
  GUI(uint16_t window_width, uint16_t window_height);

  void render(RenderWindow *window);

  bool checkClicked(Vector2i coords);

  void addObject(const string &name, UIDrawable *drawable);

  UIDrawable *get(const string &name);

 private:
  uint16_t window_width, window_height;
  map<string, UIDrawable *> drawables;

};