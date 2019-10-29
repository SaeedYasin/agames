/********************************************************************
  Egg.h - Used to create eggs on OzOLED.
  2018 Copyright (c) electronicbeans.com  All right reserved.

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

#include "OzOLED.h"
#include "Point.h"

class Snake;

class Egg : public OzOLED 
{
  public:
    Egg();
    Egg(Snake*);
    ~Egg();
    Point getPosition(void);
    void move(Snake*);

    friend bool isValidEgg(Egg*, Snake*);

  private:
    Point position;
    void findPosition(Snake*);
    void draw(void);
};

#endif
