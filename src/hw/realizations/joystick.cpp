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
#include "InputEvent.h"
#include "OsInterface.h"

static OsInterface *g_os = NULL;
static Joystick *g_js = NULL;
static dir_t g_pressedKey = NONE;

Joystick::Joystick(OsInterface *os)
{
  g_js = this;
  g_os = os;

  pinMode(UP_PIN, INPUT);
  pinMode(CENTER_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);

  setTimer1Frequency(20); // 20 Hz -> 50ms
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

ISR(TIMER1_COMPA_vect)
{
  if (g_js != NULL)
  {
    dir_t key = g_js->getUserInput();

    if (key == NONE)
    {
      g_pressedKey = key;
      return;
    }

    if (g_pressedKey != key)
    {
      g_pressedKey = key;
      g_js->generateInputEvent(key);
    }
  }
}

dir_t Joystick::scanIOs(void)
{
  dir_t key = NONE;

  if (digitalRead(UP_PIN) == LOW)
    key = UP;
  else if (digitalRead(CENTER_PIN) == LOW)
    key = CENTER;
  else if (digitalRead(LEFT_PIN) == LOW)
    key = LEFT;
  else if (digitalRead(DOWN_PIN) == LOW)
    key = DOWN;
  else if (digitalRead(RIGHT_PIN) == LOW)
    key = RIGHT;

  return key;
}

void Joystick::generateInputEvent(dir_t key)
{
  Event *pEvent = NULL;

  switch (key)
  {
  case UP:
    pEvent = new InputEvent(InputEvent::UP_KEY_PRESSED);
    break;
  case CENTER:
    pEvent = new InputEvent(InputEvent::CENTER_KEY_PRESSED);
    break;
  case LEFT:
    pEvent = new InputEvent(InputEvent::LEFT_KEY_PRESSED);
    break;
  case DOWN:
    pEvent = new InputEvent(InputEvent::DOWN_KEY_PRESSED);
    break;
  case RIGHT:
    pEvent = new InputEvent(InputEvent::RIGHT_KEY_PRESSED);
    break;
  default:
    g_os->log("Joystick: UnHandled key %d", (uint8_t)key);
    break;
  }

  if (pEvent)
  {
    notifyListeners(pEvent);
    delete pEvent;
  }
}

dir_t Joystick::getUserInput(void)
{
  return scanIOs();
}

dir_t Joystick::waitForUserInput(void)
{
  dir_t key = NONE;

  while (key == NONE)
    key = getUserInput();

  return key;
}
