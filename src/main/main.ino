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
#include "src/ArduinoOs.h"
#include "src/GameSelection.h"
#include "src/Joystick.h"
#include "src/OzOLED.h"

DisplayInterface *display;
GameSelection *pGameSelection;
InputInterface *joystick;
OsInterface *os;

void setup(void)
{
  os = new ArduinoOs();
  joystick = new Joystick();
  display = new OzOLED();

  pGameSelection = new GameSelection(os, display, joystick);

  // SYSLED - indicates system is working
  //#define SYSLED   13
  // pinMode(SYSLED, OUTPUT);
  // digitalWrite(SYSLED, HIGH); // Toggle System LED
  // digitalWrite(SYSLED, LOW); // Toggle System LED
}

void loop(void)
{
  pGameSelection->loop();
}
