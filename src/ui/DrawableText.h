#include <codecvt>

#include "UIDrawable.h"

class DrawableText : public UIDrawable {
 public:
  DrawableText(Vector2s position, const std::string &text, uint8_t charSize, Font *font, Color color);

  void Render(RenderWindow *window) override;

  [[nodiscard]] bool CheckClicked(Vector2i coords) override { return false; };

  [[nodiscard]] bool IsClickable() override { return false; };

 private:
  Text text_;
};
