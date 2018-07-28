/*
  snake.cpp - Used to create a snake on OzOLED.
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
*/
#ifndef __SNAKE_H
#define __SNAKE_H

#include "OzOLED.h"
#include "Joystick.h"


struct snakeCell
{
  byte col, row;            // Postiton coordinates on screen for snake cell
                            // col can vary from 0 to 15, row from 0 to 7 only.
  snakeCell *preSnakeCell;  // Pointer to the previous snake cell.
};

// Declare class egg for friend function
class Egg;

class Snake : public OzOLED
{  
  public:
      Snake();
      ~Snake();
      void drawSnakeCell(byte,byte);
      void removeSnakeCell(byte,byte);
      void drawSnake();
      void removeSnake();
      byte moveSnake();
      snakeCell* findSnakeTail();
      void setSnakeDir(byte);
      byte getSnakeDir();
      byte detectSnakeSelfCollision();
      void setSnakeSpeed(byte);
      byte getSnakeSpeed();
      void AdjustSnakeSpeed();
      byte getSnakeLength();
      void killSnakeAnimation();
      void displayResult();
      void operator ++(int);
      byte getSnakeHeadCol();
      byte getSnakeHeadRow();

      friend byte checkForValidEgg(Egg*,Snake*);

  private:
      byte length;               // Can be from 3 to a maximum of 128 
      byte speed;                // Speed of snake - can be from 5 (slowest) to 1 (highest)
      byte dir;                  // Can be UP, DOWN, LEFT, RIGHT only
      snakeCell *pSnakeHead;     // Where to position snake on LCD screen
};

#endif
