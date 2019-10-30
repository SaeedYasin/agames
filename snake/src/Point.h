/********************************************************************
  Point.h - Used to create a POINT on OzOLED.
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
#ifndef __POINT_H
#define __POINT_H

#include "OzOLED.h"

#define DISP_POINT_SIZE   8
#define DISP_MAX_X        OzOLED_Max_X/DISP_POINT_SIZE
#define DISP_MAX_Y        OzOLED_Max_Y/DISP_POINT_SIZE

class Point
{
  public:
    byte x;
    byte y;

    Point();
    ~Point();
    Point(byte, byte);

    void operator=(const Point&);
    bool operator==(const Point&);
    bool operator<(const Point&);
};

const Point DISP_MAX_SIZE(DISP_MAX_X, DISP_MAX_Y);

#endif
