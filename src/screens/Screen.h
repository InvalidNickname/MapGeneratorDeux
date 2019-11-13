#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"

class Screen {

 public:
  explicit Screen(sf::RenderWindow *_window) : window(_window) {}

  virtual void prepare() = 0;

  virtual GameState doAction() = 0;

  virtual void draw() = 0;

 protected:
  sf::RenderWindow *window;
  GameState temp_key{THIS_STATE};

};