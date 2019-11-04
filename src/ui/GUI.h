#include <map>

#include <string>

#include "UIDrawable.h"

using namespace std;

class GUI {
 public:
  void render(RenderWindow *window);

  bool checkClicked(Vector2i coords);

  void addObject(const string &name, UIDrawable *drawable);

  [[nodiscard]] UIDrawable *get(const string &name) const;

 private:
  map<string, UIDrawable *> drawables;

};