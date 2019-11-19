#include "drawable_text.h"

DrawableText::DrawableText(Vector2s position, const std::string &text, uint8_t charSize, Font *font, Color color) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  text_ = Text(converter.from_bytes(text), *font, charSize);
  text_.setPosition(position.x, position.y);
  text_.setFillColor(color);
}

void DrawableText::Render(sf::RenderWindow *window) {
  window->draw(text_);
}
