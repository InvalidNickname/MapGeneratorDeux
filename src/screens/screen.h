#ifndef MGD_SRC_SCREENS_SCREEN_H
#define MGD_SRC_SCREENS_SCREEN_H

#include <SFML/Graphics.hpp>

#include "game_state.h"

class Screen {

 public:
  explicit Screen(sf::RenderWindow *window) : window_(window) {}

  virtual void Prepare() = 0;

  virtual GameState DoAction() = 0;

  virtual void Draw() = 0;

 protected:
  sf::RenderWindow *window_;
  GameState temp_state_{THIS_STATE};
};

#endif