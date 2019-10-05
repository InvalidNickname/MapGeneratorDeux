#include <map>

#include <utils/AssetLoader.h>
#include <ui/UIDrawable.h>

class GUI {
  public:
    GUI(float windowWidth, float windowHeight);

    void render(RenderWindow *window);

    bool checkClicked(float _x, float _y);

    void addObject(const string &name, UIDrawable *drawable);

    UIDrawable *get(const string &name);

  private:
    float windowWidth, windowHeight;
    map<string, UIDrawable *> drawables;

};