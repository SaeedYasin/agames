/*
  egg.cpp - Used to create eggs on OzOLED.
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
*/
#ifndef __EGG_H
#define __EGG_H

#include "OzOLED.h"
#include "Snake.h"


class Egg : public OzOLED 
{
  public:
    Egg();
    Egg(Snake*);
    ~Egg();
    byte getEggCol();
    byte getEggRow();
    void moveEgg(Snake*);

    friend byte checkForValidEgg(Egg*, Snake*);

  private:
    byte x;     // Can have value from 0 to 15 only
    byte y;     // Can have value from 0 to 7 only

    void drawEgg(byte, byte);
};

#endif
