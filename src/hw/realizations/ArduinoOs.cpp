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
#include "ArduinoOs.h"
#include <Arduino.h>

ArduinoOs::ArduinoOs(void)
{
}

ArduinoOs::~ArduinoOs(void)
{
}

int16_t ArduinoOs::analogRead(uint8_t pin)
{
  return analogRead(pin);
}

void ArduinoOs::randomSeed(int16_t seed)
{
  randomSeed(seed);
}

int32_t ArduinoOs::random(uint16_t max)
{
  return random(max);
}

void ArduinoOs::delay(uint32_t ms)
{
  delay(ms);
}
