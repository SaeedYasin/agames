/********************************************************************
  snake.h - Used to create a snake on OzOLED.
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

#include "ozOLED.h"
#include "joystick.h"

#define DISP_POINT_SIZE   8
#define DISP_MAX_X        OzOLED_Max_X/DISP_POINT_SIZE
#define DISP_MAX_Y        OzOLED_Max_Y/DISP_POINT_SIZE

class Point
{
  public:
    byte x;   // x can vary from 0 to 15 (DISP_MAX_X)
    byte y;   // y can vary from 0 to 7  (DISP_MAX_Y)

    Point() {}
    ~Point() {}

    Point(byte x, byte y)
    {
      this->x = x;
      this->y = y;
    }

    void operator=(const Point& p)
    {
      this->x = p.x;
      this->y = p.y;
    }

    bool operator==(const Point& p)
    {
      return ((this->x == p.x) && (this->y == p.y));
    }

    bool operator<(const Point& p)
    {
      return ((this->x < p.x) && (this->y < p.y));
    }
};

const Point DISP_MAX_SIZE(DISP_MAX_X, DISP_MAX_Y);

struct SnakeCell
{
  Point position; // Postiton coordinates on screen for snake cell
  SnakeCell *preSnakeCell; // Pointer to the previous snake cell
};

// Declare class egg for friend function
class Egg;

class Snake : public OzOLED
{  
  public:
    Snake();
    ~Snake();
    byte move();
    void setSnakeDir(byte);
    byte getSnakeDir();
    void setSnakeSpeed(byte);
    byte getSnakeSpeed();
    void AdjustSnakeSpeed();
    byte getSnakeLength();
    void killSnakeAnimation();
    void displayResult();
    void operator ++(int);
    byte getSnakeHeadCol();
    byte getSnakeHeadRow();

    friend bool isValidEgg(Egg*, Snake*);

  private:
    byte length;  // Can be from 3 to a maximum of 128
    byte speed;   // Speed of snake - can be from 5 (slowest) to 1 (highest)
    byte dir;     // Can be UP, DOWN, LEFT, RIGHT only
    SnakeCell *pSnakeHead;
    byte detectSnakeSelfCollision();
    void drawSnakeCell(byte, byte);
    void removeSnakeCell(byte, byte);
    void drawSnake();
    void removeSnake();
    SnakeCell* findSnakeTail();
};

#endif
