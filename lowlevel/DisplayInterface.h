/********************************************************************
  DisplayInterface.h
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
#ifndef __DISPLAY_INTERFACE_H
#define __DISPLAY_INTERFACE_H

#include "Point.h"


#define DISP_POINT_SIZE   8


struct Pixel
{
  Point position;
  uint8_t data[DISP_POINT_SIZE];
};


class DisplayInterface
{
  public:
    DisplayInterface();
    virtual ~DisplayInterface();
    virtual void clearScreen(void);
    virtual void printPixel(const Pixel Pix) = 0;
	  virtual void printString(const char* String, uint8_t numChar, Point Pos) = 0;
	  virtual void printBigNumber(const char* number, uint8_t numChar, Point Pos) = 0;

    const uint8_t MAX_X(void);
    const uint8_t MAX_Y(void);
    const Point MAX_SIZE(void);

  protected:
    uint8_t m_max_x;
    uint8_t m_max_y;
    Point m_max_size;
};

#endif
