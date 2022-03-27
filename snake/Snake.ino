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
#include <Arduino.h>
#include "src/Snake.h"
#include "src/Joystick.h"
#include "src/DisplayInterface.h"
#include "src/OzOLED.h"
#include "src/Egg.h"

void displayResult(void);

DisplayInterface *display;
Snake *snake;
Joystick *joyStick;
Egg *egg;
Turn inputDir;

void setup(void)
{
  joyStick = new Joystick;
  display = new OzOLED();

  snake = new Snake(display);
  egg = new Egg(display, snake);
  inputDir = NONE;

  // SYSLED - indicates system is working
  //#define SYSLED   13
  // pinMode(SYSLED, OUTPUT);
  // digitalWrite(SYSLED, HIGH); // Toggle System LED
  // digitalWrite(SYSLED, LOW); // Toggle System LED
}

void loop(void)
{
  if (inputDir == NONE || inputDir == CENTER || inputDir == snake->getDirection())
  {
    for (byte s = 0; s < 25; s++)
    {
      delay(snake->getSpeed());
      inputDir = joyStick->getUserInput();

      if ((inputDir != NONE) && (inputDir != CENTER) && (inputDir != snake->getDirection()))
        break;
    }
  }

  // Check if user pressed any button
  if (inputDir == NONE)
    inputDir = joyStick->getUserInput();

  // Check for valid input
  if ((inputDir != NONE) && (inputDir != CENTER) && (inputDir != snake->getDirection()))
  {
    snake->setDirection(inputDir);
    inputDir = NONE;
  }

  if (!(snake->move()))
  {
    uint8_t snakeLength = snake->getLength();
    delete snake;
    delete egg;

    displayResult(snakeLength);
    joyStick->waitForUserInput();
    display->clearScreen();
    snake = new Snake(display);
    egg = new Egg(display, snake);
    inputDir = NONE;
  }

  // Check if snake eats the egg
  if (egg->getPosition() == snake->getHeadPosition())
  {
    (*snake)++;
    egg->move(snake);
  }

  if (inputDir == NONE || inputDir == CENTER || inputDir == snake->getDirection())
  {
    for (byte s = 0; s < 25; s++)
    {
      delay(snake->getSpeed());
      inputDir = joyStick->getUserInput();

      if ((inputDir != NONE) && (inputDir != CENTER) && (inputDir != snake->getDirection()))
        break;
    }
  }
}

void displayResult(uint8_t length)
{
  char gScore = static_cast<char>(length);
  gScore -= 3;

  if (gScore < 10)
  {
    gScore += 0x30;
    display->printBigNumber(&gScore, 1, Point(6, 1));
  }
  else if (gScore < 100)
  {
    char gS[2];
    gS[0] = static_cast<char>(gScore / 10) + 0x30;
    gS[1] = static_cast<char>(gScore % 10) + 0x30;

    display->printBigNumber(gS, 2, Point(4, 1));
  }
  else
  {
    char gS[3];
    gS[0] = static_cast<char>(gScore / 100) + 0x30;
    gS[1] = (static_cast<char>(gScore / 10)) - (gS[0] - 0x30) * 10 + 0x30;
    gS[2] = static_cast<char>(gScore % 10) + 0x30;

    display->printBigNumber(gS, 3, Point(1, 3));
  }

  display->printString("Try again?", 10, Point(3, 6));
}
