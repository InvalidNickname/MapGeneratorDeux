#ifndef MGD_SRC_UTILS_R_H
#define MGD_SRC_UTILS_R_H

#include <cstdint>

struct R {
 public:
  static constexpr float kTileHeight = 80.f;
  static constexpr float kTileWidth = 69.282032302755091741097853660235f;

  static const uint16_t kMinimapHeight = 190;
  static const uint16_t kMinimapWidth = 300;
  static const uint16_t kMapModeButtonHeight = 31;
  static const uint16_t kMapModeButtonWidth = 41;
  static const uint16_t kTileInfoListWidth = 320;
  static const uint16_t kTileInfoListHeight = 120;
  static const uint16_t kSRadioWidth = 700;
  static const uint16_t kSRadioHeight = 150;
  static const uint16_t kSCheckSize = kSRadioHeight / 3;
  static const uint16_t kGoSize = 120;
};

#endif