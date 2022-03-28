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
#ifndef __EGG_H
#define __EGG_H

#include "DisplayInterface.h"

class Snake;

class Egg
{
public:
  Egg();
  Egg(DisplayInterface *, Snake *);
  virtual ~Egg();
  Point getPosition(void);
  void move(Snake *);

  friend bool isValidEgg(Egg *, Snake *);

private:
  Point m_position;
  DisplayInterface *m_display;

  void findPosition(Snake *);
  void draw(void);
  void undraw(void);
};

#endif
