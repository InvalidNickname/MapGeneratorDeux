#include <vector>

#include <screens/splashscreen/AssetLoader.h>
#include <ui/UIDrawable.h>

class GUI {
  public:
    GUI(float windowWidth, float windowHeight);

    void render(RenderWindow *window);

    bool checkClicked(float _x, float _y);

    void addDrawables(UIDrawable *drawable);

  private:
    float windowWidth, windowHeight;
    std::vector<UIDrawable *> drawables;

};