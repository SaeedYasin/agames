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
#include "Joystick.h"
#include <Arduino.h>

Joystick::Joystick(void)
{
  pinMode(UP, INPUT);
  pinMode(CENTER, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(RIGHT, INPUT);

  setTimer1Frequency(5);
}

Joystick::~Joystick(void)
{
}

void Joystick::setTimer1Frequency(uint8_t freq)
{
  cli(); // stop interrupts

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (15625 / freq) - 1; // (16*10^6) / (freq*1024) - 1 (must be <65536)
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  sei(); // allow interrupts
}

byte test = 0;
ISR(TIMER1_COMPA_vect)
{
  test = 1;
}

dir_t Joystick::scanIOs(void)
{
  dir_t key = NONE;

  if (digitalRead(UP) == LOW)
    key = UP;
  else if (digitalRead(CENTER) == LOW)
    key = CENTER;
  else if (digitalRead(LEFT) == LOW)
    key = LEFT;
  else if (digitalRead(DOWN) == LOW)
    key = DOWN;
  else if (digitalRead(RIGHT) == LOW)
    key = RIGHT;

  return key;
}

dir_t Joystick::getUserInput(void)
{
  if (test == 1)
    return scanIOs();
  else
    return NONE;
}

dir_t Joystick::waitForUserInput(void)
{
  dir_t key = NONE;

  while (key == NONE)
    key = getUserInput();

  return key;
}
