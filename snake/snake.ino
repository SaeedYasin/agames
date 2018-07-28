/*
  snake.ino - Snake mini game designed for LCD 0.96 inch display.
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

#include "src/snake.h"
#include "src/egg.h"

// SYSLED - indicates system is working
#define SYSLED   13

// Globals for this game
Snake * snake;
Joystick * joyS;
Egg * egg;
byte Input_Dir; 


void setup(void)
{
  // Random values are used to create location for eggs
  randomSeed(analogRead(0));    

  snake = new Snake;
  joyS = new Joystick;
  egg = new Egg(snake);
  Input_Dir = 0; 

  pinMode(SYSLED, OUTPUT);
}

void loop(void)
{                            
  digitalWrite(SYSLED, HIGH); // Toggle System LED

  if( Input_Dir == 0 || Input_Dir == CENTER || Input_Dir == snake->getSnakeDir() )
  {
    for(byte s=0;s<25;s++)
    {
      delay(snake->getSnakeSpeed());
      Input_Dir = joyS->getUserInput();
  
      if( (Input_Dir != 0) && (Input_Dir != CENTER) && (Input_Dir != snake->getSnakeDir()) ) 
        break;
    }
  }

  // Check if user pressed any button
  if(Input_Dir == 0)
    Input_Dir = joyS->getUserInput();

  // Check for valid input
  if( (Input_Dir != 0) && (Input_Dir != CENTER) && (Input_Dir != snake->getSnakeDir()) )
  {
    snake->setSnakeDir(Input_Dir);
    Input_Dir = 0;
  }  

  // Move snake and check if snake is within bounds
  if(snake->moveSnake())    
  {
    snake->killSnakeAnimation();
    snake->displayResult();
    delete snake;
    delete egg;

    joyS->waitForUserInput();
    snake = new Snake;
    egg = new Egg(snake);
    Input_Dir = 0;
  }

  // Check if snake eats that egg
  if( (egg->getEggCol() == snake->getSnakeHeadCol()) && 
      (egg->getEggRow() == snake->getSnakeHeadRow()) )
  {
    (*snake)++;
    egg->moveEgg(snake);
  }

  // Adjust snake speed depending upon its length
  snake->AdjustSnakeSpeed();

  digitalWrite(SYSLED, LOW); // Toggle System LED

  if( Input_Dir == 0 || Input_Dir == CENTER || Input_Dir == snake->getSnakeDir() )
  {
    for(byte s=0;s<25;s++)
    {
      delay(snake->getSnakeSpeed());
      Input_Dir = joyS->getUserInput();

      if( (Input_Dir != 0) && (Input_Dir != CENTER) && (Input_Dir != snake->getSnakeDir()) )
        break;
    }
  }
}
