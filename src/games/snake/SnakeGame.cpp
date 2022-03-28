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

SnakeGame::SnakeGame(OsInterface *pOS, DisplayInterface *pDisp, InputInterface *pInput)
    : m_os(pOS), m_display(pDisp), m_input(pInput)
{
  m_display->clearScreen();

  m_snake = new Snake(m_display, m_os);
  m_egg = new Egg(m_display, m_snake, m_os);
  m_inputDir = NONE;
}

SnakeGame::~SnakeGame(void)
{
  delete m_snake;
  delete m_egg;
}

void SnakeGame::loop(void)
{
  while (m_gameActive)
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

    if (!(m_snake->move()))
    {
      uint8_t snakeLength = m_snake->getLength();
      delete m_snake;
      delete m_egg;

      displayResult(snakeLength);
      dir_t key = m_input->waitForUserInput();

      if (key != DOWN)
      {
        m_display->clearScreen();
        m_snake = new Snake(m_display, m_os);
        m_egg = new Egg(m_display, m_snake, m_os);
        m_inputDir = NONE;
      }
      else
      {
        m_gameActive = false;
      }
    }

    // Check if snake eats the egg
    if (m_egg->getPosition() == m_snake->getHeadPosition())
    {
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
  }
}

void SnakeGame::displayResult(uint8_t length)
{
  char gScore = static_cast<char>(length);
  gScore -= 3;

  if (gScore < 10)
  {
    gScore += 0x30;
    m_display->printBigNumber(&gScore, 1, Point(6, 1));
  }
  else if (gScore < 100)
  {
    char gS[2];
    gS[0] = static_cast<char>(gScore / 10) + 0x30;
    gS[1] = static_cast<char>(gScore % 10) + 0x30;

    m_display->printBigNumber(gS, 2, Point(4, 1));
  }
  else
  {
    char gS[3];
    gS[0] = static_cast<char>(gScore / 100) + 0x30;
    gS[1] = (static_cast<char>(gScore / 10)) - (gS[0] - 0x30) * 10 + 0x30;
    gS[2] = static_cast<char>(gScore % 10) + 0x30;

    m_display->printBigNumber(gS, 3, Point(1, 3));
  }

  m_display->printString("Try again?", 10, Point(3, 6));
  m_display->printString("Exit", 5, Point(5, 7));
}
