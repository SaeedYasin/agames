/********************************************************************
  joystick.h - Joystick Driver Library
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
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include <Arduino.h>

// Define joystick pin constants
#define UP      2
#define CENTER  3
#define LEFT    4
#define DOWN    5
#define RIGHT   6

class Joystick
{
  public:
    Joystick();
    ~Joystick();
    byte getUserInput();
    byte waitForUserInput();

  private:
    byte scanIOs();
};

#endif
