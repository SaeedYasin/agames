/********************************************************************
  Joystick.cpp - Joystick Driver Library
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
#include "Joystick.h"


Joystick::Joystick(void)
{
  pinMode(UP, INPUT);
  pinMode(CENTER, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(RIGHT, INPUT);
}

Joystick::~Joystick(void)
{
}

byte Joystick::scanIOs(void)
{
  byte key = 0;

  if(digitalRead(UP)==LOW)
    key = UP;
  else if(digitalRead(CENTER)==LOW)
    key = CENTER;
  else if(digitalRead(LEFT)==LOW)
    key = LEFT;
  else if(digitalRead(DOWN)==LOW)
    key = DOWN;
  else if(digitalRead(RIGHT)==LOW)
    key = RIGHT;

  return key;
}

byte Joystick::getUserInput(void)
{
  return scanIOs();
}

byte Joystick::waitForUserInput(void)
{
  byte key = 0;

  while(key==0)
    key = getUserInput();

  return key;
}
