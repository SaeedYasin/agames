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
#include "SnakeGame.h"
#include "DisplayInterface.h"
#include "Egg.h"
#include "InputEvent.h"
#include "InputInterface.h"
#include "OsInterface.h"
#include "Snake.h"
#include <stddef.h>
#include <stdlib.h>

SnakeGame::SnakeGame(OsInterface *pOS, DisplayInterface *pDisp, InputInterface *pInput)
    : m_os(pOS), m_display(pDisp), m_input(pInput)
{
  init();
  registerForInputEvents();
}

SnakeGame::~SnakeGame(void)
{
  unregisterForInputEvents();
  cleanup();
}

void SnakeGame::registerForInputEvents(void)
{
  uint16_t inputEvents[] = {InputEvent::UP_KEY_PRESSED, InputEvent::LEFT_KEY_PRESSED,
                            InputEvent::DOWN_KEY_PRESSED, InputEvent::RIGHT_KEY_PRESSED};
  uint16_t totalEvents = sizeof(inputEvents) / sizeof(inputEvents[0]);
  m_input->registerListener(this, inputEvents, totalEvents);
}

void SnakeGame::unregisterForInputEvents(void)
{
  uint16_t inputEvents[] = {InputEvent::UP_KEY_PRESSED, InputEvent::LEFT_KEY_PRESSED,
                            InputEvent::DOWN_KEY_PRESSED, InputEvent::RIGHT_KEY_PRESSED};
  uint16_t totalEvents = sizeof(inputEvents) / sizeof(inputEvents[0]);
  m_input->unregisterListener(this, inputEvents, totalEvents);
}

void SnakeGame::eventOccurred(const Event *const event)
{
  uint16_t eventValue = event->getValue();

  switch (eventValue)
  {
  case InputEvent::UP_KEY_PRESSED:
    m_inputDirection = UP;
    break;
  case InputEvent::LEFT_KEY_PRESSED:
    m_inputDirection = LEFT;
    break;
  case InputEvent::DOWN_KEY_PRESSED:
    m_inputDirection = DOWN;
    break;
  case InputEvent::RIGHT_KEY_PRESSED:
    m_inputDirection = RIGHT;
    break;
  default:
    m_os->log("SnakeGame: unknown event received %d", eventValue);
    break;
  }
}

void SnakeGame::init(void)
{
  m_display->clearScreen();
  m_snake = new Snake(m_display, m_os);
  m_egg = new Egg(m_display, m_snake, m_os);
  m_inputDirection = RIGHT;
}

void SnakeGame::cleanup(void)
{
  if (m_snake != NULL)
  {
    delete m_snake;
    m_snake = NULL;
  }

  if (m_egg != NULL)
  {
    delete m_egg;
    m_egg = NULL;
  }
}

bool SnakeGame::loop(void)
{
  for (uint8_t s = 0; s < 50; s++)
  {
    m_os->delayMs(m_snake->getSpeed());

    // Break early if new input received
    if (m_inputDirection != m_snake->getDirection())
      break;
  }

  m_snake->setDirection(m_inputDirection);

  // Check if snake can move
  if ((m_snake->move()) == false)
  {
    uint8_t snakeLength = m_snake->getLength();
    cleanup();
    displayResult(snakeLength);

    dir_t key = waitForUserInput();
    m_os->log("SnakeGame: waited for user input of %d", key);

    if (key != LEFT)
      init();
    else
      return false;
  }

  // Check if snake eats the egg
  if (m_egg->getPosition() == m_snake->getHeadPosition())
  {
    Point eggPos = m_egg->getPosition();
    m_os->log("SnakeGame: Snake ate the egg at x=%d,y=%d", eggPos.x, eggPos.y);
    (*m_snake)++;
    m_egg->move(m_snake);
  }

  return true;
}

dir_t SnakeGame::waitForUserInput(void)
{
  m_inputDirection = NONE;

  while (m_inputDirection == NONE)
  {
    m_os->delayMs(50);
  }

  return m_inputDirection;
}

void SnakeGame::displayResult(uint8_t length)
{
  char buffer[3] = {0};
  char gScore = static_cast<char>(length);
  gScore -= 3; // Subtract initial snake length
  itoa(gScore, buffer, 10);

  m_display->printBigNumber(buffer, 3, Point(gScore > 9 ? 4 : 6, 0));
  m_display->printString("Try again?", 10, Point(3, 5));
  m_display->printString("< Exit", 7, Point(0, 7));
}
