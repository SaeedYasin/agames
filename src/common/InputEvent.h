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
#ifndef __INPUT_EVENT_H
#define __INPUT_EVENT_H

#include "Event.h"

class InputEvent : public Event
{
public:
  InputEvent(uint16_t event);
  virtual ~InputEvent();

  typedef enum Event_t
  {
    FAMILY_TYPE = 0x0100,
    UNKNOWN_EVENT = FAMILY_TYPE + 0,
    UP_KEY_PRESSED = FAMILY_TYPE + 1,
    CENTER_KEY_PRESSED = FAMILY_TYPE + 2,
    LEFT_KEY_PRESSED = FAMILY_TYPE + 3,
    DOWN_KEY_PRESSED = FAMILY_TYPE + 4,
    RIGHT_KEY_PRESSED = FAMILY_TYPE + 5,
  } event_t;
};

#endif
