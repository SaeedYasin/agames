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
#include <stddef.h>

GameSelection *GameSelection::m_instance = NULL;

GameSelection *GameSelection::getInstance()
{
  if (m_instance == NULL)
    m_instance = new GameSelection();

  return m_instance;
}

void GameSelection::destroyInstance()
{
  if (m_instance != NULL)
  {
    delete m_instance;
    m_instance = NULL;
  }
}

void GameSelection::setOS(OsInterface *pOS)
{
  m_os = pOS;
}

void GameSelection::setDisplay(DisplayInterface *pDisp)
{
  m_display = pDisp;
}

void GameSelection::setInput(InputInterface *pInput)
{
  m_input = pInput;
}

GameSelection::GameSelection()
{
  m_currentGame = NULL;
}

GameSelection::~GameSelection(void)
{
}

void GameSelection::drawSelectionScreen(void)
{
  m_display->clearScreen();
  m_display->printString("Please select", 14, Point(1, 0));
  m_display->printString("a game...", 10, Point(3, 1));
  m_display->printString("> Snake", 7, Point(4, 4));
}

Game *GameSelection::getSelectedGame(void)
{
  drawSelectionScreen();
  m_os->delayMs(1000);
  return new SnakeGame(m_os, m_display, m_input);
}

void GameSelection::loop(void)
{
  if (m_currentGame == NULL)
  {
    m_currentGame = getSelectedGame();
  }

  bool currentGameActive = m_currentGame->loop();

  if (!currentGameActive)
  {
    delete m_currentGame;
    m_currentGame = NULL;
  }
}
