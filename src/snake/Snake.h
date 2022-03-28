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
#ifndef __SNAKE_H
#define __SNAKE_H

#include "Point.h"
#include <stdint.h>
#include "types.h"

class DisplayInterface;
class Egg;
class OsInterface;

struct SnakeCell
{
  Point position;
  SnakeCell *preSnakeCell;
};

class Snake
{
public:
  Snake(DisplayInterface *, OsInterface *);
  virtual ~Snake();
  bool move(void);
  void setDirection(dir_t);
  dir_t getDirection(void);
  uint8_t getSpeed(void);
  uint8_t getLength(void);
  void operator++(int);
  Point getHeadPosition(void);

  friend bool isValidEgg(Egg *, Snake *);

private:
  enum speed_t
  {
    VERYFAST = 1,
    FAST = 2,
    NORMAL = 3,
    SLOW = 4,
    VERYSLOW = 5
  };

  uint8_t m_length;
  dir_t m_direction;
  speed_t m_speed;
  DisplayInterface *m_display;
  OsInterface *m_OS;

  SnakeCell *pSnakeHead;
  bool selfCollision(void);
  void drawCell(Point);
  void undrawCell(Point);
  void draw(void);
  void undraw(void);
  SnakeCell *findTail(void);
  SnakeCell *findSecondLastCell(void);
  void adjustSpeed(void);
  void animateDying(void);
  void reverse(void);
};

#endif
