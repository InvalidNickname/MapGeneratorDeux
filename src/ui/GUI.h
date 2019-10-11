#include <map>

#include <utils/AssetLoader.h>
#include "UIDrawable.h"

class GUI {
 public:
  GUI(uint16_t windowWidth, uint16_t windowHeight);

  void render(RenderWindow *window);

  bool checkClicked(Vector2i coords);

  void addObject(const string &name, UIDrawable *drawable);

  UIDrawable *get(const string &name);

 private:
  uint16_t windowWidth, windowHeight;
  map<string, UIDrawable *> drawables;

};