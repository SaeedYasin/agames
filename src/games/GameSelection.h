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
#ifndef __GAME_SELECTION_H
#define __GAME_SELECTION_H

class DisplayInterface;
class Game;
class InputInterface;
class OsInterface;

class GameSelection
{
public:
  static GameSelection *getInstance();
  static void destroyInstance();
  void loop(void);

  void setOS(OsInterface *);
  void setDisplay(DisplayInterface *);
  void setInput(InputInterface *);

private:
  GameSelection();
  virtual ~GameSelection();

  static GameSelection *m_instance;

  OsInterface *m_os;
  DisplayInterface *m_display;
  InputInterface *m_input;
  Game *m_currentGame;

  void drawSelectionScreen(void);
  Game *getSelectedGame(void);
};

#endif
