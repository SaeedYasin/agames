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
#ifndef __OS_INTERFACE_H
#define __OS_INTERFACE_H

#include <stdint.h>

class OsInterface
{
public:
  OsInterface();
  virtual ~OsInterface();

  virtual int16_t analogRead(uint8_t) = 0;
  virtual void randomSeed(int16_t) = 0;
  virtual int32_t random(uint16_t) = 0;
  virtual void delay(uint32_t) = 0;
};

#endif
