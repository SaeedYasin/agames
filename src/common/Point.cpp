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
#include "Point.h"

Point::Point(void)
{
}

Point::Point(uint8_t x, uint8_t y)
{
  this->x = x;
  this->y = y;
}

Point::~Point(void)
{
}

void Point::operator=(const Point &p)
{
  this->x = p.x;
  this->y = p.y;
}

bool Point::operator==(const Point &p) const
{
  return ((this->x == p.x) && (this->y == p.y));
}

bool Point::operator!=(const Point &p) const
{
  return ((this->x != p.x) || (this->y != p.y));
}

bool Point::operator<(const Point &p) const
{
  return ((this->x < p.x) && (this->y < p.y));
}
