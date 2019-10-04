#include <vector>

#include <ui/Button.h>
#include <screens/splashscreen/AssetLoader.h>

class GUI {
  public:
    GUI(int windowWidth, int windowHeight);

    void render(RenderWindow *window);

    bool checkClick(int _x, int _y);

    void addButton(Button *button);

  private:
    int windowWidth, windowHeight;
    std::vector<Button *> buttons;

};