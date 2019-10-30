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
Joystick* joyStick;
Egg* egg;
Turn inputDir;


void setup(void)
{
  // TODO
  display = new OzOLED();
  display->clearDisplay();
  // change to game display / play ?
  // add observer

  snake = new Snake;
  joyStick = new Joystick;
  egg = new Egg(snake);
  inputDir = NONE;

  pinMode(SYSLED, OUTPUT);
}

void loop(void)
{
  digitalWrite(SYSLED, HIGH); // Toggle System LED

  if( inputDir == NONE || inputDir == CENTER || inputDir == snake->getDirection() )
  {
    for(byte s=0;s<25;s++)
    {
      delay(snake->getSpeed());
      inputDir = joyStick->getUserInput();
  
      if( (inputDir != NONE) && (inputDir != CENTER) && (inputDir != snake->getDirection()) )
        break;
    }
  }

  // Check if user pressed any button
  if(inputDir == NONE)
    inputDir = joyStick->getUserInput();

  // Check for valid input
  if( (inputDir != NONE) && (inputDir != CENTER) && (inputDir != snake->getDirection()) )
  {
    snake->setDirection(inputDir);
    inputDir = NONE;
  }

  if(!(snake->move()))
  {
    delete snake;
    delete egg;

    joyStick->waitForUserInput();
    display->clearDisplay();
    snake = new Snake;
    egg = new Egg(snake);
    inputDir = NONE;
  }

  // Check if snake eats the egg
  if(egg->getPosition() == snake->getHeadPosition())
  {
    (*snake)++;
    egg->move(snake);
  }

  digitalWrite(SYSLED, LOW); // Toggle System LED

  if( inputDir == NONE || inputDir == CENTER || inputDir == snake->getDirection() )
  {
    for(byte s=0;s<25;s++)
    {
      delay(snake->getSpeed());
      inputDir = joyStick->getUserInput();

      if( (inputDir != NONE) && (inputDir != CENTER) && (inputDir != snake->getDirection()) )
        break;
    }
  }
}
