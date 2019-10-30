/********************************************************************
  Snake.h - Used to create a snake on OzOLED.
  2018 Copyright (c) electronicbeans.com  All right reserved.

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

#include "OzOLED.h"
#include "Point.h"
#include "Joystick.h"


class Egg;

struct SnakeCell
{
  Point position;
  SnakeCell* preSnakeCell;
};

class Snake : public OzOLED
{  
  public:
    Snake();
    ~Snake();
    bool move(void);
    void setDirection(Turn);
    Turn getDirection(void);
    byte getSpeed(void);
    byte getLength(void);
    void operator ++(int);
    Point getHeadPosition(void);

    friend bool isValidEgg(Egg*, Snake*);

  private:
    enum speed_t
    {
      VERYFAST= 1,
      FAST = 2,
      NORMAL = 3,
      SLOW = 4,
      VERYSLOW = 5
    };

    byte m_length;
    Turn m_direction;
    speed_t m_speed;

    SnakeCell* pSnakeHead;
    bool selfCollision(void);
    void drawCell(Point);
    void undrawCell(Point);
    void draw(void);
    void undraw(void);
    SnakeCell* findTail(void);
    void adjustSpeed(void);
    void animateDying(void);
    void displayResult(void);
    void reverse(void);
};

#endif
