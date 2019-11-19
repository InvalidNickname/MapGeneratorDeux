#ifndef MGD_SRC_UI_RADIO_BUTTONS_H
#define MGD_SRC_UI_RADIO_BUTTONS_H

#include <map>
#include <string>

#include "button.h"

using namespace std;

class RadioButtons : public UIDrawable {
 public:
  RadioButtons(map<string, Button *> *buttons, const string &default_clicked);

  void Render(RenderWindow *window) override;

  [[nodiscard]] bool CheckClicked(Vector2i coords) override;

  [[nodiscard]] bool IsClickable() override { return true; }

  void SetClicked(const string &name);

 private:
  map<string, Button *> *buttons_;
  string clicked_;
};

#endif