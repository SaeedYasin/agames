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

#include "Snake.h"


Snake::Snake(void)
 : length(3), dir(RIGHT), speed(5)
{
  pSnakeHead = new snakeCell;
  pSnakeHead->col = 3;
  pSnakeHead->row = 3;

  snakeCell *pM = new snakeCell;
  pSnakeHead->preSnakeCell = pM;
  pM->col = 2;
  pM->row = 3;

  snakeCell *pT = new snakeCell;
  pM->preSnakeCell = pT;
  pT->col = 1;
  pT->row = 3;
  pT->preSnakeCell = NULL;

  // Clear LCD screen
  Snake::clearDisplay();

  // Draw snake on display
  Snake::drawSnake();
}

Snake::~Snake(void)
{
  snakeCell *pNextCell, *pCurrentCell;
  pCurrentCell = pSnakeHead;
  
  // Delete all the snake cells
  for(byte i=0;i<length;i++)
  {
    pNextCell = pCurrentCell->preSnakeCell;
    delete pCurrentCell;

    pCurrentCell = pNextCell;
  }
}

void Snake::drawSnakeCell(byte col, byte row)
{
  if(col < 16 && row < 8) 
  {
    setCursorXY(col, row);

    // Display snake cells
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
  if(col < 16 && row < 8)
  {
    setCursorXY(col, row);

    for(byte i=0;i<8;i++)
      sendData(0x00); 
  }  
}

void Snake::drawSnake(void)
{
  snakeCell *pCell = pSnakeHead;
    
  for(byte i=0;i<length;i++)
  {
    drawSnakeCell(pCell->col,pCell->row);
    pCell = pCell->preSnakeCell;
  }
}

void Snake::removeSnake(void)
{
  snakeCell *pCell = pSnakeHead;
    
  for(byte i=0;i<length;i++)
  {
    removeSnakeCell(pCell->col,pCell->row);
    pCell = pCell->preSnakeCell;
  }
}

// Return 0 for successful move, 1 for if snake gets out of bounds
byte Snake::moveSnake(void)
{
  snakeCell *pTailCell = findSnakeTail();

  switch(dir)
  {
    case RIGHT:
                if(((pSnakeHead->col)+1) < 16)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->col, pTailCell->row);

                  pTailCell->col = pSnakeHead->col + 1;
                  pTailCell->row = pSnakeHead->row;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;
                  
                  drawSnakeCell(pSnakeHead->col, pSnakeHead->row);
                }
                else
                    return 1;
                break;
    case UP:
                if((pSnakeHead->row) != 0)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->col, pTailCell->row);

                  pTailCell->col = pSnakeHead->col;
                  pTailCell->row = pSnakeHead->row - 1;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;

                  drawSnakeCell(pSnakeHead->col, pSnakeHead->row);
                }
                else
                    return 1;
                break;
    case LEFT:
                if((pSnakeHead->col) != 0)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->col, pTailCell->row);

                  pTailCell->col = pSnakeHead->col - 1;
                  pTailCell->row = pSnakeHead->row;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;

                  drawSnakeCell(pSnakeHead->col, pSnakeHead->row);
                }
                else
                    return 1;
                break;
    case DOWN:
                if(((pSnakeHead->row)+1) < 8)
                {
                  if(detectSnakeSelfCollision())
                    return 1;

                  removeSnakeCell(pTailCell->col, pTailCell->row);

                  pTailCell->col = pSnakeHead->col;
                  pTailCell->row = pSnakeHead->row + 1;
                  pTailCell->preSnakeCell = pSnakeHead;
                  pSnakeHead = pTailCell;

                  drawSnakeCell(pSnakeHead->col, pSnakeHead->row);
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
snakeCell* Snake::findSnakeTail(void)
{  
  snakeCell *pHeadCell = pSnakeHead;
  snakeCell *pTailCell;

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
  snakeCell *pCell = pSnakeHead->preSnakeCell;

  switch(dir)
  {
    case RIGHT:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->col+1) == pCell->col  &&  pSnakeHead->row == pCell->row )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
    case UP:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->row-1) == pCell->row  &&  pSnakeHead->col == pCell->col )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
    case LEFT:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->col-1) == pCell->col  &&  pSnakeHead->row == pCell->row )
                    return 1;

                  pCell = pCell->preSnakeCell;
                }
                break;
    case DOWN:
                for(byte i=0;i<(length-1);i++)
                {
                  if( (pSnakeHead->row+1) == pCell->row  &&  pSnakeHead->col == pCell->col )
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

  // Clear LCD screen
  Snake::clearDisplay();
}

void Snake::operator ++(int)
{
  snakeCell *pCell = new snakeCell;
  snakeCell *pTail = findSnakeTail();

  pCell->col = pTail->col;
  pCell->row = pTail->row;
  
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
  return pSnakeHead->col;
}

byte Snake::getSnakeHeadRow(void)
{
  return pSnakeHead->row;
}
