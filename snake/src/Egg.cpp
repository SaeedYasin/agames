/********************************************************************
  Egg.cpp - Used to create eggs on OzOLED.
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
#include "Egg.h"
#include "Snake.h"


// Friend function used to make sure not to create egg on the snake
bool isValidEgg(Egg* pE, Snake* pS)
{
  bool isValid = true;
  SnakeCell* pCell = pS->pSnakeHead;

  for(byte i=0;i<pS->m_length;i++)
  {
    if(pE->position == pCell->position)
    {
      isValid = false;
      break;
    }

    pCell = pCell->preSnakeCell;
  }

  return isValid;
}

Egg::Egg(void)
{  
}

Egg::Egg(Snake* pS)
{
  // Seed random value from ADC
  randomSeed(analogRead(0));

  findPosition(pS);
  draw();
}

Egg::~Egg(void)
{
  undraw();
}

void Egg::findPosition(Snake* pS)
{
  do
  {
    position.x = random(DISP_MAX_X);
    position.y = random(DISP_MAX_Y);

  } while(!isValidEgg(this, pS));
}

void Egg::draw(void)
{
  if(position < DISP_MAX_SIZE)
  {
    setCursorXY(position.x, position.y);

    // Draw egg
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

void Egg::undraw(void)
{
  if(position < DISP_MAX_SIZE)
  {
    setCursorXY(position.x, position.y);

    for(byte i=0;i<DISP_POINT_SIZE;i++)
      sendData(0x00);
  }
}

Point Egg::getPosition(void)
{
  return position;
}

void Egg::move(Snake* pS)
{  
  findPosition(pS);
  draw();
}
