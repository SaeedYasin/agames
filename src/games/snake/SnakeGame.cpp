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
#include "InputInterface.h"
#include "OsInterface.h"
#include "Snake.h"
#include <stddef.h>
#include <stdlib.h>

SnakeGame::SnakeGame(OsInterface *pOS, DisplayInterface *pDisp, InputInterface *pInput)
    : m_os(pOS), m_display(pDisp), m_input(pInput)
{
  init();
}

SnakeGame::~SnakeGame(void)
{
  cleanup();
}

void SnakeGame::init(void)
{
  m_display->clearScreen();
  m_snake = new Snake(m_display, m_os);
  m_egg = new Egg(m_display, m_snake, m_os);
  m_inputDir = NONE;
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
  if (m_inputDir == NONE || m_inputDir == CENTER || m_inputDir == m_snake->getDirection())
  {
    for (uint8_t s = 0; s < 25; s++)
    {
      m_os->delayMs(m_snake->getSpeed());
      m_inputDir = m_input->getUserInput();

      if ((m_inputDir != NONE) && (m_inputDir != CENTER) && (m_inputDir != m_snake->getDirection()))
        break;
    }
  }

  // Check if user pressed any button
  if (m_inputDir == NONE)
    m_inputDir = m_input->getUserInput();

  // Check for valid input
  if ((m_inputDir != NONE) && (m_inputDir != CENTER) && (m_inputDir != m_snake->getDirection()))
  {
    m_snake->setDirection(m_inputDir);
    m_inputDir = NONE;
  }

  if ((m_snake->move()) == false)
  {
    uint8_t snakeLength = m_snake->getLength();
    cleanup();
    displayResult(snakeLength);

    dir_t key = m_input->waitForUserInput();

    if (key != LEFT)
      init();
    else
      return false;
  }

  // Check if snake eats the egg
  if (m_egg->getPosition() == m_snake->getHeadPosition())
  {
    m_os->log("Snake ate the egg at x=%d,y=%d", m_egg->getPosition().x, m_egg->getPosition().y);
    (*m_snake)++;
    m_egg->move(m_snake);
  }

  if (m_inputDir == NONE || m_inputDir == CENTER || m_inputDir == m_snake->getDirection())
  {
    for (uint8_t s = 0; s < 25; s++)
    {
      m_os->delayMs(m_snake->getSpeed());
      m_inputDir = m_input->getUserInput();

      if ((m_inputDir != NONE) && (m_inputDir != CENTER) && (m_inputDir != m_snake->getDirection()))
        break;
    }
  }

  return true;
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
