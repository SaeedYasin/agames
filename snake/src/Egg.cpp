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

Egg::Egg(DisplayInterface* display, Snake* pS)
{
  // Seed random value from ADC
  randomSeed(analogRead(0));

  m_display = display;
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
    position.x = random(m_display->MAX_X());
    position.y = random(m_display->MAX_Y());

  } while(!isValidEgg(this, pS));
}

void Egg::draw(void)
{
  const Pixel eggPixel = {position, {0x00,0x18,0x3c,0x7e,0x7e,0x3c,0x18,0x00}};
  m_display->printPixel(eggPixel);
}

void Egg::undraw(void)
{
  const Pixel clearPixel = {position, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
  m_display->printPixel(clearPixel);
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
