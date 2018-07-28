/*
  egg.cpp - Used to create eggs on OzOLED.
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

#include "egg.h"


// Friend function used to make sure not to create egg on the snake
byte checkForValidEgg(Egg *pE, Snake *pS)
{
  snakeCell *pCell = pS->pSnakeHead;
  
  for(byte i=0;i<pS->length;i++)
  {
    if(pE->x == pCell->col && pE->y == pCell->row)
      return 1;

    pCell = pCell->preSnakeCell;
  }

  return 0;
}

Egg::Egg(void)
{  
}

Egg::Egg(Snake *pS)
{
  do
  {
    x = random(16);
    y = random(8);
    
  } while(checkForValidEgg(this, pS));

  drawEgg(x, y);
}

Egg::~Egg(void)
{  
}

void Egg::drawEgg(byte col, byte row)
{
  if(col < 16 && row < 8)
  {
    setCursorXY(col, row);

    // draw egg
    sendData(0x00); 
    sendData(0x18);
    sendData(0x3c);
    sendData(0x7e);
    sendData(0x7e);
    sendData(0x3c);
    sendData(0x18);
    sendData(0x00);
  } 
}

byte Egg::getEggCol(void)
{
  return x;
}

byte Egg::getEggRow(void)
{
  return y;
}

void Egg::moveEgg(Snake* pS)
{  
  do
  {
    x = random(16);
    y = random(8);
    
  } while(checkForValidEgg(this, pS));

  drawEgg(x, y);
}
