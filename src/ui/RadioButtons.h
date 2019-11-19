#pragma once

#include <map>
#include <string>

#include "Button.h"

using namespace std;

class RadioButtons : public UIDrawable {
 public:
  RadioButtons(map<string, Button *> *buttons, const string &default_clicked);

  void Render(RenderWindow *window) override;

  [[nodiscard]] bool CheckClicked(Vector2i coords) override;

  [[nodiscard]] bool IsClickable() override { return true; }

  void setClicked(const string &name);

 private:
  map<string, Button *> *buttons;

  string clicked;
};
