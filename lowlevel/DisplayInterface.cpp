/********************************************************************
  DisplayInterface.cpp
  2019 Copyright (c) electronicbeans.com  All right reserved.

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
#include "DisplayInterface.h"


DisplayInterface::DisplayInterface(void)
{
}

DisplayInterface::~DisplayInterface(void)
{
}

const uint8_t DisplayInterface::MAX_X(void)
{
  return m_max_x;
}

const uint8_t DisplayInterface::MAX_Y(void)
{
  return m_max_y;
}

const Point DisplayInterface::MAX_SIZE(void)
{
  return m_max_size;
}
