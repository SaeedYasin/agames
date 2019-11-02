/********************************************************************
  Snake.cpp - Used to create a snake on OzOLED.
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
#include "Snake.h"


Snake::Snake(DisplayInterface* display)
 : m_length(3), m_direction(RIGHT), m_speed(VERYSLOW), m_display(NULL)
{
  pSnakeHead = new SnakeCell;
  pSnakeHead->position.x = 3;
  pSnakeHead->position.y = 3;

  SnakeCell* pM = new SnakeCell;
  pSnakeHead->preSnakeCell = pM;
  pM->position.x = 2;
  pM->position.y = 3;

  SnakeCell* pT = new SnakeCell;
  pM->preSnakeCell = pT;
  pT->position.x = 1;
  pT->position.y = 3;
  pT->preSnakeCell = NULL;

  m_display = display;
  draw();
}

Snake::~Snake(void)
{
  animateDying();
  undraw();

  SnakeCell *pNextCell, *pCurrentCell;
  pCurrentCell = pSnakeHead;

  for(byte i=0;i<m_length;i++)
  {
    pNextCell = pCurrentCell->preSnakeCell;
    delete pCurrentCell;

    pCurrentCell = pNextCell;
  }
}

void Snake::drawCell(Point Pos)
{
  const Pixel snakePixel = {Pos, {0x00,0x3c,0x7e,0x7e,0x7e,0x7e,0x7e,0x3c}};
  m_display->printPixel(snakePixel);
}

void Snake::undrawCell(Point Pos)
{
  const Pixel clearPixel = {Pos, {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
  m_display->printPixel(clearPixel);
}

void Snake::draw(void)
{
  SnakeCell* pCell = pSnakeHead;
    
  for(byte i=0;i<m_length;i++)
  {
    drawCell(pCell->position);
    pCell = pCell->preSnakeCell;
  }
}

void Snake::undraw(void)
{
  SnakeCell* pCell = pSnakeHead;

  for(byte i=0;i<m_length;i++)
  {
    undrawCell(pCell->position);
    pCell = pCell->preSnakeCell;
  }
}

bool Snake::move(void)
{
  bool success = false;
  Point newPosition;

  if(!selfCollision())
  {
    switch(m_direction)
    {
      case RIGHT:
        if(((pSnakeHead->position.x)+1) < m_display->MAX_X())
        {
          newPosition.x = pSnakeHead->position.x + 1;
          newPosition.y = pSnakeHead->position.y;
          success = true;
        }
        break;

      case UP:
        if((pSnakeHead->position.y) != 0)
        {
          newPosition.x = pSnakeHead->position.x;
          newPosition.y = pSnakeHead->position.y - 1;
          success = true;
        }
        break;

      case LEFT:
        if((pSnakeHead->position.x) != 0)
        {
          newPosition.x = pSnakeHead->position.x - 1;
          newPosition.y = pSnakeHead->position.y;
          success = true;
        }
        break;

      case DOWN:
        if(((pSnakeHead->position.y)+1) < m_display->MAX_Y())
        {
          newPosition.x = pSnakeHead->position.x;
          newPosition.y = pSnakeHead->position.y + 1;
          success = true;
        }
        break;

      default:
        success = false;
        break;
    }
  }

  if(success)
  {
    SnakeCell* pTailCell = findTail();
    undrawCell(pTailCell->position);

    pTailCell->position = newPosition;
    pTailCell->preSnakeCell = pSnakeHead;
    pSnakeHead = pTailCell;

    drawCell(pSnakeHead->position);
  }

  return success;
}

SnakeCell* Snake::findTail(void)
{
  SnakeCell* pHeadCell = pSnakeHead;
  SnakeCell* pTailCell;

  for(byte i=0;i<(m_length-1);i++)
  {
    pTailCell = pHeadCell->preSnakeCell;
    pHeadCell = pTailCell;
  }

  return pTailCell;
}

bool Snake::selfCollision(void)
{
  SnakeCell* pCell = pSnakeHead->preSnakeCell;
  bool collision = false;
  byte index = 0;

  switch(m_direction)
  {
    case RIGHT:
      for(index=0;index<(m_length-1);index++)
      {
        if((pSnakeHead->position.x+1) == pCell->position.x
         && pSnakeHead->position.y == pCell->position.y)
        {
          collision = true;
          break;
        }

        pCell = pCell->preSnakeCell;
      }
      break;

    case UP:
      for(index=0;index<(m_length-1);index++)
      {
        if((pSnakeHead->position.y-1) == pCell->position.y
         && pSnakeHead->position.x == pCell->position.x)
        {
          collision = true;
          break;
        }

        pCell = pCell->preSnakeCell;
      }
      break;

    case LEFT:
      for(index=0;index<(m_length-1);index++)
      {
        if((pSnakeHead->position.x-1) == pCell->position.x
         && pSnakeHead->position.y == pCell->position.y)
        {
          collision = true;
          break;
        }

        pCell = pCell->preSnakeCell;
      }
      break;

    case DOWN:
      for(index=0;index<(m_length-1);index++)
      {
        if((pSnakeHead->position.y+1) == pCell->position.y
         && pSnakeHead->position.x == pCell->position.x)
        {
          collision = true;
          break;
        }

        pCell = pCell->preSnakeCell;
      }
      break;

    default:
      break;
  }

  if(collision && index == 0)
  {
    // Reverse snake direction in the case snake head
    // collided with the cell right behind snake head cell
    // This move is allowed, so don't declare collision as true
    collision = false;
    reverse();
  }

  return collision;
}

void Snake::reverse(void)
{
  SnakeCell* ppreCell = NULL;
  SnakeCell* pcurrCell = pSnakeHead;
  SnakeCell* pnextCell = pcurrCell->preSnakeCell;
  pcurrCell->preSnakeCell = NULL;

  for(byte i=0;i<(m_length-1);i++)
  {
    ppreCell = pcurrCell;
    pcurrCell = pnextCell;
    pnextCell = pcurrCell->preSnakeCell;
    pcurrCell->preSnakeCell = ppreCell;
  }

  pSnakeHead = pcurrCell;
}

Turn Snake::getDirection(void)
{
  return m_direction;
}

void Snake::setDirection(Turn direction)
{
  if(direction == RIGHT || direction == LEFT ||
     direction == UP    || direction == DOWN)
  {
    m_direction = direction;
  }
}

byte Snake::getSpeed(void)
{
  return static_cast<byte>(m_speed);
}

void Snake::adjustSpeed(void)
{
  if(m_length<4)
    m_speed = VERYSLOW;
  else if(m_length>=4 && m_length<5)
    m_speed = SLOW;
  else if(m_length>=5 && m_length<8)
    m_speed = NORMAL;
  else if(m_length>=8 && m_length<15)
    m_speed = FAST;
  else if(m_length>=15)
    m_speed = VERYFAST;
}

uint8_t Snake::getLength(void)
{
  return m_length;
}

void Snake::operator ++(int)
{
  SnakeCell* pCell = new SnakeCell;
  SnakeCell* pTail = findTail();

  pCell->position.x = pTail->position.x;
  pCell->position.y = pTail->position.y;
  
  pTail->preSnakeCell = pCell;
  pCell->preSnakeCell = NULL;

  m_length++;

  adjustSpeed();
}

void Snake::animateDying(void)
{
  for(byte i=0;i<4;i++)
  {
    undraw();
    delay(150);
    draw();
    delay(150);
  }
}

Point Snake::getHeadPosition(void)
{
  return pSnakeHead->position;
}
