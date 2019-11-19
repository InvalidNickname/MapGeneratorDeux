#ifndef MGD_SRC_SCREENS_SCREEN_MANAGER_H
#define MGD_SRC_SCREENS_SCREEN_MANAGER_H

#include "screen.h"

class ScreenManager {
 public:
  explicit ScreenManager(GameState initial_key, uint32_t length);

  void AddScreen(GameState state, Screen *screen);

  bool DoActiveScreenActions();

  void DrawActiveScreen();

 private:
  GameState state_, temp_state_{SPLASHSCREEN}, prev_state_{EXIT};

  std::vector<Screen *> screens_;
};

#endif