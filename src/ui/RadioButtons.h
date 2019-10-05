#include <map>
#include <string>

#include "UIDrawable.h"
#include "Button.h"

using namespace std;

class RadioButtons : public UIDrawable {
  public:
    RadioButtons(map<string, Button *> *buttons, const string &name);

    void render(RenderWindow *window) override;

    bool checkClicked(float _x, float _y) override;

    bool isClickable() override { return true; }

    void setClicked(const string &name);

  private:
    map<string, Button *> *buttons;
};