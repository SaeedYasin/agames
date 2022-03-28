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
#ifndef __ARDUINO_OS_H
#define __ARDUINO_OS_H

#include "OsInterface.h"

class ArduinoOs : public OsInterface
{
public:
  ArduinoOs();
  virtual ~ArduinoOs();

  int16_t analogRead(uint8_t);
  void randomSeed(int16_t);
  int32_t random(uint16_t);
  void delay(uint32_t);
};

#endif
