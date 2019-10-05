#include "UIDrawable.h"
#include "Button.h"

class RadioButtons : public UIDrawable {
  public:
    RadioButtons(std::vector<Button *> buttons, int clicked);

    void render(RenderWindow *window) override;

    bool checkClicked(float _x, float _y) override;

    bool isClickable() override { return true; }

  private:
    std::vector<Button *> buttons;
};
