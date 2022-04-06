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
#ifndef __OS_INTERFACE_H
#define __OS_INTERFACE_H

#include <stdint.h>

typedef enum LogType
{
  NO_LOG_TYPE = 0x00,
  SERIAL_LOG_TYPE = 0x01
} log_t;

class OsInterface
{
public:
  OsInterface();
  virtual ~OsInterface();

  virtual void seedRandomFromADC(void) = 0;
  virtual int32_t getRandomValue(uint16_t) = 0;
  virtual void delayMs(uint32_t) = 0;

  virtual bool isEnabled(log_t);
  virtual void setLogEnable(log_t, bool);
  virtual void log(const char *, ...);

protected:
  log_t m_logType;
};

#endif
