/********************************************************************
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
********************************************************************/
#include "Snake.h"


Snake::Snake(void)
 : length(3), dir(RIGHT), speed(5)
{
  pSnakeHead = new SnakeCell;
  pSnakeHead->position.x = 3;
  pSnakeHead->position.y = 3;

  SnakeCell *pM = new SnakeCell;
  pSnakeHead->preSnakeCell = pM;
  pM->position.x = 2;
  pM->position.y = 3;

  SnakeCell *pT = new SnakeCell;
  pM->preSnakeCell = pT;
  pT->position.x = 1;
  pT->position.y = 3;
  pT->preSnakeCell = NULL;

  clearDisplay();
  drawSnake();
}

Snake::~Snake(void)
{
  SnakeCell *pNextCell, *pCurrentCell;
  pCurrentCell = pSnakeHead;

  for(byte i=0;i<length;i++)
  {
    pNextCell = pCurrentCell->preSnakeCell;
    delete pCurrentCell;

    pCurrentCell = pNextCell;
  }
}

void Snake::drawSnakeCell(byte col, byte row)
{
  if(col < DISP_MAX_X && row < DISP_MAX_Y)
  {
    setCursorXY(col, row);

    // Display snake cell lines
    sendData(0x00); 
    sendData(0x3c);
    sendData(0x7e);
    sendData(0x7e);
    sendData(0x7e);
    sendData(0x7e);
    sendData(0x7e);
    sendData(0x3c);
  }
}

void Snake::removeSnakeCell(byte col, byte row)
{
  if(col < DISP_MAX_X && row < DISP_MAX_Y)
  {
    setCursorXY(col, row);

    for(byte i=0;i<DISP_POINT_SIZE;i++)
      sendData(0x00); 
  }  
}

void Snake::drawSnake(void)
{
  SnakeCell *pCell = pSnakeHead;
    
  for(byte i=0;i<length;i++)
  {
    drawSnakeCell(pCell->position.x, pCell->position.y);
    pCell = pCell->preSnakeCell;
  }
}

void Snake::removeSnake(void)
{
  SnakeCell *pCell = pSnakeHead;
    
  for(byte i=0;i<length;i++)
  {
    removeSnakeCell(pCell->position.x, pCell->position.y);
    pCell = pCell->preSnakeCell;
  }
}

// Return 0 for successful move, 1 for if snake gets out of bounds
byte Snake::move(void)
{
  SnakeCell *pTailCell = findSnakeTail();

  switch(dir)
  {
    case RIGHT:
                if(((pSnakeHead->position.x)+1) < DISP_MAX_X)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->position.x, pTailCell->position.y);

                  pTailCell->position.x = pSnakeHead->position.x + 1;
                  pTailCell->position.y = pSnakeHead->position.y;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;
                  
                  drawSnakeCell(pSnakeHead->position.x, pSnakeHead->position.y);
                }
                else
                    return 1;
                break;
    case UP:
                if((pSnakeHead->position.y) != 0)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->position.x, pTailCell->position.y);

                  pTailCell->position.x = pSnakeHead->position.x;
                  pTailCell->position.y = pSnakeHead->position.y - 1;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;

                  drawSnakeCell(pSnakeHead->position.x, pSnakeHead->position.y);
                }
                else
                    return 1;
                break;
    case LEFT:
                if((pSnakeHead->position.x) != 0)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->position.x, pTailCell->position.y);

                  pTailCell->position.x = pSnakeHead->position.x - 1;
                  pTailCell->position.y = pSnakeHead->position.y;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;

                  drawSnakeCell(pSnakeHead->position.x, pSnakeHead->position.y);
                }
                else
                    return 1;
                break;
    case DOWN:
                if(((pSnakeHead->position.y)+1) < DISP_MAX_Y)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->position.x, pTailCell->position.y);

                  pTailCell->position.x = pSnakeHead->position.x;
                  pTailCell->position.y = pSnakeHead->position.y + 1;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;

                  drawSnakeCell(pSnakeHead->position.x, pSnakeHead->position.y);
                }
                else
                    return 1;
                break;
    default:
              return 1;
              break;
  }

  return 0;
}

// Find snake tail and return its pointer
SnakeCell* Snake::findSnakeTail(void)
{  
  SnakeCell *pHeadCell = pSnakeHead;
  SnakeCell *pTailCell;

  for(byte i=0;i<(length-1);i++)
  {
    pTailCell = pHeadCell->preSnakeCell;
    pHeadCell = pTailCell;
  }

  return pTailCell;
}

byte Snake::getSnakeDir(void)
{
  return dir;
}

void Snake::setSnakeDir(byte d)
{
  if( d == RIGHT || d == LEFT || d == UP || d == DOWN )
    dir = d;
}

// return 0 if no collision detected, otherwise return 1
byte Snake::detectSnakeSelfCollision()
{
  SnakeCell *pCell = pSnakeHead->preSnakeCell;

  switch(dir)
  {
    case RIGHT:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->position.x+1) == pCell->position.x  &&  pSnakeHead->position.y == pCell->position.y )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
    case UP:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->position.y-1) == pCell->position.y  &&  pSnakeHead->position.x == pCell->position.x )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
    case LEFT:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->position.x-1) == pCell->position.x  &&  pSnakeHead->position.y == pCell->position.y )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
    case DOWN:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->position.y+1) == pCell->position.y  &&  pSnakeHead->position.x == pCell->position.x )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
  }

  return 0;
}

void Snake::setSnakeSpeed(byte s)
{
  if(s<=5 && s>0)
    speed = s;
}

byte Snake::getSnakeSpeed(void)
{
  return speed;
}

void Snake::AdjustSnakeSpeed(void)
{
  if(length<4)
    speed = 5;
  else if(length>=4 && length<5)
    speed = 4;
  else if(length>=5 && length<8)
    speed = 3;
  else if(length>=8 && length<15)
    speed = 2;
  else if(length>=15)
    speed = 1;   
}

byte Snake::getSnakeLength(void)
{
  return length;
}

void Snake::killSnakeAnimation(void)
{
  // Animate snake dying
  for(byte i=0;i<4;i++){
    removeSnake();
    delay(150);
    drawSnake();
    delay(150);
  }

  clearDisplay();
}

void Snake::operator ++(int)
{
  SnakeCell* pCell = new SnakeCell;
  SnakeCell* pTail = findSnakeTail();

  pCell->position.x = pTail->position.x;
  pCell->position.y = pTail->position.y;
  
  pTail->preSnakeCell = pCell;
  this->length++;
}

void Snake::displayResult(void)
{
  char gScore = static_cast<char>(this->length);
  gScore -= 3;

  if(gScore<10)
  {
    gScore += 0x30;
    printBigNumber(&gScore,6,1,1);
  }
  else if(gScore<100)
  {
    char gS[2];
    gS[0] = static_cast<char>(gScore/10) + 0x30;
    gS[1] = static_cast<char>(gScore%10) + 0x30;
  
    printBigNumber(gS,4,1,2);
  }
  else
  {
    char gS[3];
    gS[0] = static_cast<char>(gScore/100) + 0x30;
    gS[1] = (static_cast<char>(gScore/10)) - (gS[0]-0x30)*10 + 0x30;
    gS[2] = static_cast<char>(gScore%10) + 0x30;

    printBigNumber(gS,3,1,3);
  }

  printString("Try again?",3,6,10);
}

byte Snake::getSnakeHeadCol(void)
{
  return pSnakeHead->position.x;
}

byte Snake::getSnakeHeadRow(void)
{
  return pSnakeHead->position.y;
}
