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
#ifndef __POINT_H
#define __POINT_H

#include <stdint.h>

class Point
{
public:
  uint8_t x;
  uint8_t y;

  Point();
  ~Point();
  Point(uint8_t, uint8_t);

  void operator=(const Point &);
  bool operator==(const Point &) const;
  bool operator!=(const Point &) const;
  bool operator<(const Point &) const;
};

#endif
