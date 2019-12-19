#include "type.h"

string Type::GetName(Level level) const {
  switch (level) {
    case NO:return name.at(3);
    case SMALL:return name.at(2);
    case MEDIUM:return name.at(1);
    case HIGH:return name.at(0);
  }
  return string(); // недостижимо
}

Color Type::GetBaseColor(Level level) const {
  switch (level) {
    case NO:return base_color.at(3);
    case SMALL:return base_color.at(2);
    case MEDIUM:return base_color.at(1);
    case HIGH:return base_color.at(0);
  }
  return Color(); // недостижимо
}
