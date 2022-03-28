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
#include "Egg.h"
#include "DisplayInterface.h"
#include "OsInterface.h"
#include "Snake.h"
#include <stdint.h>

// Friend function used to make sure not to create egg on the snake
bool isValidEgg(Egg *pE, Snake *pS)
{
  bool isValid = true;
  SnakeCell *pCell = pS->pSnakeHead;

  for (uint8_t i = 0; i < pS->m_length; i++)
  {
    if (pE->m_position == pCell->position)
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

Egg::Egg(DisplayInterface *display, Snake *pS, OsInterface *OS)
    : m_OS(OS)
{
  m_OS->seedRandomFromADC();

  m_display = display;
  findPosition(pS);
  draw();
}

Egg::~Egg(void)
{
  undraw();
}

void Egg::findPosition(Snake *pS)
{
  do
  {
    m_position.x = (uint8_t)m_OS->getRandomValue(m_display->MAX_X());
    m_position.y = (uint8_t)m_OS->getRandomValue(m_display->MAX_Y());

  } while (!isValidEgg(this, pS));
}

void Egg::draw(void)
{
  const Pixel eggPixel = {m_position, {0x00, 0x18, 0x3c, 0x7e, 0x7e, 0x3c, 0x18, 0x00}};
  m_display->printPixel(eggPixel);
}

void Egg::undraw(void)
{
  const Pixel clearPixel = {m_position, {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
  m_display->printPixel(clearPixel);
}

Point Egg::getPosition(void)
{
  return m_position;
}

void Egg::move(Snake *pS)
{
  findPosition(pS);
  draw();
}
