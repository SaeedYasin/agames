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
#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "InputInterface.h"
#include <stdint.h>
#include "types.h"

class OsInterface;

#define UP_PIN 2
#define CENTER_PIN 3
#define LEFT_PIN 4
#define DOWN_PIN 5
#define RIGHT_PIN 6

class Joystick : public InputInterface
{
public:
  Joystick(OsInterface *);
  virtual ~Joystick();

  dir_t getUserInput();
  dir_t waitForUserInput();
  void generateInputEvent(dir_t);

private:
  void setTimer1Frequency(uint8_t);
  dir_t scanIOs();
};

#endif
