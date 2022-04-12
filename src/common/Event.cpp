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
#include "Event.h"

Event::Event(uint16_t event)
{
  m_event = event;
}

Event::~Event(void)
{
}

uint8_t Event::getFamily(void) const
{
  return static_cast<uint8_t>(m_event >> 8);
}

uint8_t Event::getType(void) const
{
  return static_cast<uint8_t>(m_event);
}

uint16_t Event::getValue(void) const
{
  return m_event;
}
