#include <map>

#include <utils/AssetLoader.h>
#include "UIDrawable.h"

class GUI {
  public:
    GUI(unsigned short windowWidth, unsigned short windowHeight);

    void render(RenderWindow *window);

    bool checkClicked(Vector2i coords);

    void addObject(const string &name, UIDrawable *drawable);

    UIDrawable *get(const string &name);

  private:
    unsigned short windowWidth, windowHeight;
    map<string, UIDrawable *> drawables;

};