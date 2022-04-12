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
#ifndef __NOTIFIER_H
#define __NOTIFIER_H

#include <stddef.h>
#include <stdint.h>

class Event;
class Listener;

class Notifier
{
public:
  Notifier();
  virtual ~Notifier();

  void registerListener(Listener *listener, uint16_t event);
  bool unregisterListener(Listener *listener, uint16_t event);
  void registerListener(Listener *listener, uint16_t eventsList[], uint16_t eventsListSize);
  bool unregisterListener(Listener *listener, uint16_t eventsList[], uint16_t eventsListSize);

protected:
  void notifyListeners(const Event *const event);

private:
  class ListenerNode
  {
  public:
    ListenerNode(Listener *listener, uint16_t event, ListenerNode *next = NULL);
    virtual ~ListenerNode();
    bool is(Listener *listener, uint16_t event);

    Listener *m_listener;
    uint16_t m_event;
    ListenerNode *m_next;
  };

private:
  ListenerNode *m_firstListenerNode;
};

#endif
