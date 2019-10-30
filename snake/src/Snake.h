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


struct SnakeCell
{
  Point position; // Postiton coordinates on screen for snake cell
  SnakeCell* preSnakeCell; // Pointer to the previous snake cell
};

class Egg;

class Snake : public OzOLED
{  
  public:
    Snake();
    ~Snake();
    bool move(void);
    void setDirection(byte);
    byte getDirection(void);
    byte getSpeed(void);
    byte getSnakeLength(void);
    void operator ++(int);
    Point getHeadPosition(void);

    friend bool isValidEgg(Egg*, Snake*);

  private:
    byte m_length;    // Can be from 3 to a maximum of 128
    byte m_direction; // Can be UP, DOWN, LEFT, RIGHT only
    byte m_speed;     // Speed of snake - can be from 5 (slowest) to 1 (highest)

    SnakeCell* pSnakeHead;
    bool selfCollision(void);
    void drawCell(Point);
    void removeCell(Point);
    void draw(void);
    void remove(void);
    SnakeCell* findTail(void);
    void adjustSpeed(void);
    void animateDying(void);
    void displayResult(void);
    void reverse(void);
};

#endif
