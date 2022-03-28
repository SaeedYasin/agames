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
#include "GameSelection.h"
#include "DisplayInterface.h"
#include "Game.h"
#include "InputInterface.h"
#include "OsInterface.h"
#include "SnakeGame.h"

GameSelection::GameSelection(OsInterface *pOS, DisplayInterface *pDisp, InputInterface *pInput)
    : m_os(pOS), m_display(pDisp), m_input(pInput)
{
}

GameSelection::~GameSelection(void)
{
}

void GameSelection::drawSelectionScreen(void)
{
  m_display->clearScreen();
  m_display->printString("Please select", 14, Point(1, 0));
  m_display->printString("a game...", 10, Point(3, 1));
  m_display->printString("=> Snake", 8, Point(3, 4));
}

Game *GameSelection::getSelectedGame(void)
{
  drawSelectionScreen();
  m_os->delayMs(1000);
  return new SnakeGame(m_os, m_display, m_input);
}

void GameSelection::loop(void)
{
  Game *pGame = getSelectedGame();
  pGame->loop();
  delete pGame;
}
