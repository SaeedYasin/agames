/********************************************************************
  Snake.ino - Snake mini game designed for LCD 0.96 inch display.
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
#include <Arduino.h>
#include "src/Snake.h"
#include "src/Joystick.h"
#include "src/OzOLED.h"
#include "src/Egg.h"

// SYSLED - indicates system is working
#define SYSLED   13

// Globals for this game
OzOLED* display;
Snake* snake;
Joystick* joyS;
Egg* egg;
byte inputDir;


void setup(void)
{
  display = new OzOLED();  // change to game display
  snake = new Snake;
  joyS = new Joystick;
  egg = new Egg(snake);
  inputDir = 0;

  pinMode(SYSLED, OUTPUT);
}

void loop(void)
{
  digitalWrite(SYSLED, HIGH); // Toggle System LED

  if( inputDir == 0 || inputDir == CENTER || inputDir == snake->getDirection() )
  {
    for(byte s=0;s<25;s++)
    {
      delay(snake->getSpeed());
      inputDir = joyS->getUserInput();
  
      if( (inputDir != 0) && (inputDir != CENTER) && (inputDir != snake->getDirection()) )
        break;
    }
  }

  // Check if user pressed any button
  if(inputDir == 0)
    inputDir = joyS->getUserInput();

  // Check for valid input
  if( (inputDir != 0) && (inputDir != CENTER) && (inputDir != snake->getDirection()) )
  {
    snake->setDirection(inputDir);
    inputDir = 0;
  }

  if(!(snake->move()))
  {
    delete snake;
    delete egg;

    joyS->waitForUserInput();
    snake = new Snake;
    egg = new Egg(snake);
    inputDir = 0;
  }

  // Check if snake eats the egg
  if(egg->getPosition() == snake->getHeadPosition())
  {
    (*snake)++;
    egg->move(snake);
  }

  digitalWrite(SYSLED, LOW); // Toggle System LED

  if( inputDir == 0 || inputDir == CENTER || inputDir == snake->getDirection() )
  {
    for(byte s=0;s<25;s++)
    {
      delay(snake->getSpeed());
      inputDir = joyS->getUserInput();

      if( (inputDir != 0) && (inputDir != CENTER) && (inputDir != snake->getDirection()) )
        break;
    }
  }
}
