#ifndef MGD_SRC_UI_GUI_H
#define MGD_SRC_UI_GUI_H

#include <map>

#include <string>

#include "ui_drawable.h"

using namespace std;

class GUI {
 public:
  void Render(RenderWindow *window);

  bool CheckClicked(Vector2i coords);

  void AddObject(const string &name, UIDrawable *drawable);

  [[nodiscard]] UIDrawable *Get(const string &name) const;

 private:
  map<string, UIDrawable *> drawables_;
};

#endif