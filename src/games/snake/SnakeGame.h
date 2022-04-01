/********************************************************************
  2022 Copyright (c) saeedsolutions.blogspot.com
  All right reserved.

  Author: Saeed Yasin

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
********************************************************************/
#ifndef __SNAKE_GAME_H
#define __SNAKE_GAME_H

#include "Game.h"
#include <stdint.h>
#include "types.h"

class DisplayInterface;
class Egg;
class InputInterface;
class OsInterface;
class Snake;

class SnakeGame : public Game
{
public:
  SnakeGame(OsInterface *, DisplayInterface *, InputInterface *);
  virtual ~SnakeGame();

  bool loop(void);

private:
  OsInterface *m_os;
  DisplayInterface *m_display;
  InputInterface *m_input;

  Snake *m_snake;
  Egg *m_egg;
  dir_t m_inputDir;

  void init(void);
  void cleanup(void);
  void displayResult(uint8_t);
};

#endif
