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
#include "Notifier.h"
#include "Event.h"
#include "Listener.h"

Notifier::Notifier(void)
{
  m_firstListenerNode = NULL;
}

Notifier::~Notifier(void)
{
  ListenerNode *pCurrentNode = m_firstListenerNode;

  while (pCurrentNode != NULL)
  {
    m_firstListenerNode = pCurrentNode->m_next;
    delete pCurrentNode;
    pCurrentNode = m_firstListenerNode;
  }
}

void Notifier::registerListener(Listener *listener, uint16_t eventsList[], uint16_t eventsListSize)
{
  for (uint16_t i = 0; i < eventsListSize; i++)
  {
    registerListener(listener, eventsList[i]);
  }
}

bool Notifier::unregisterListener(Listener *listener, uint16_t eventsList[], uint16_t eventsListSize)
{
  bool success = true;

  for (uint16_t i = 0; i < eventsListSize; i++)
  {
    success = success & unregisterListener(listener, eventsList[i]);
  }

  return success;
}

void Notifier::registerListener(Listener *listener, uint16_t event)
{
  m_firstListenerNode = new ListenerNode(listener, event, m_firstListenerNode);
}

bool Notifier::unregisterListener(Listener *listener, uint16_t event)
{
  bool found = false;
  ListenerNode *pCurrentNode = m_firstListenerNode;
  ListenerNode *pPreviousNode = NULL;

  while (pCurrentNode != NULL)
  {
    if (pCurrentNode->is(listener, event))
    {
      found = true;

      if (pPreviousNode == NULL)
      {
        m_firstListenerNode = pCurrentNode->m_next;
        delete pCurrentNode;
        pCurrentNode = m_firstListenerNode;
      }
      else
      {
        pPreviousNode->m_next = pCurrentNode->m_next;
        delete pCurrentNode;
        pCurrentNode = pPreviousNode;
      }
    }

    pPreviousNode = pCurrentNode;
    pCurrentNode = (pCurrentNode == NULL) ? NULL : pCurrentNode->m_next;
  }

  return found;
}

void Notifier::notifyListeners(const Event *const event)
{
  uint16_t eventValue = event->getValue();
  ListenerNode *pCurrentNode = m_firstListenerNode;

  while (pCurrentNode != NULL)
  {
    if (pCurrentNode->m_event == eventValue)
    {
      pCurrentNode->m_listener->eventOccurred(event);
    }

    pCurrentNode = pCurrentNode->m_next;
  }
}

Notifier::ListenerNode::ListenerNode(Listener *listener, uint16_t event, ListenerNode *next)
    : m_listener(listener), m_event(event), m_next(next)
{
}

Notifier::ListenerNode::~ListenerNode()
{
}

bool Notifier::ListenerNode::is(Listener *listener, uint16_t event)
{
  return (m_listener == listener) && (m_event == event);
}
