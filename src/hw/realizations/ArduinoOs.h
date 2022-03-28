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

  void seedRandomFromADC(void);
  int32_t getRandomValue(uint16_t);
  void delayMs(uint32_t);
};

#endif
