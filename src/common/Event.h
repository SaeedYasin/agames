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
#ifndef __EVENT_H
#define __EVENT_H

#include <stdint.h>

class Event
{
public:
  Event(uint16_t event);
  virtual ~Event();

  virtual uint8_t getFamily(void) const;
  virtual uint8_t getType(void) const;
  virtual uint16_t getValue(void) const;

protected:
  uint16_t m_event;
};

#endif
