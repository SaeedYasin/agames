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
#include "ArduinoOs.h"
#include <Arduino.h>
#include "stdarg.h"

#define MAX_LOG_BUFFER_SIZE 256
static char LOG_ERROR_MSG[] = "non-printable message";

ArduinoOs::ArduinoOs(void)
    : m_logType(NO_LOG_TYPE)
{
  log("System initialized - using C++%ld", __cplusplus);
}

ArduinoOs::~ArduinoOs(void)
{
}

void ArduinoOs::seedRandomFromADC(void)
{
  randomSeed(analogRead(0));
}

int32_t ArduinoOs::getRandomValue(uint16_t max)
{
  return random(max);
}

void ArduinoOs::delayMs(uint32_t ms)
{
  delay(ms);
}

bool ArduinoOs::sanitizeLogBuffer(char *buffer, int bufferSize, int noOfBytesWritten)
{
  // Check fot encoding error
  if (noOfBytesWritten < 0)
    return false;

  // Check for buffer overflow
  if (noOfBytesWritten > (int)bufferSize - 1)
    return false;

  // Ensure null termination
  buffer[noOfBytesWritten] = '\0';

  return true;
}

bool ArduinoOs::isEnabled(log_t log)
{
  bool isEnabled = false;

  if (log == NO_LOG_TYPE)
    isEnabled = m_logType != NO_LOG_TYPE;
  else
    isEnabled = (unsigned char)(m_logType & log) > 0;

  return isEnabled;
}

void ArduinoOs::setLogEnable(log_t log, bool enable)
{
  if (enable)
  {
    m_logType = (log_t)(m_logType | log);
  }
  else
  {
    m_logType = (log_t)(m_logType & ~log);
  }

  handleLogTypeChange();
}

void ArduinoOs::handleLogTypeChange(void)
{
  if (isEnabled(SERIAL_LOG_TYPE))
  {
    Serial.begin(115200);
    while (!Serial)
    {
    }
  }
  else
  {
    Serial.end();
  }
}

void ArduinoOs::log(const char *msg, ...)
{
  if (isEnabled())
  {
    char buffer[MAX_LOG_BUFFER_SIZE];
    int bufferSize = sizeof(buffer);

    va_list args;
    va_start(args, msg);
    int noOfBytesWritten = vsnprintf(buffer, bufferSize, msg, args);
    va_end(args);

    bool success = sanitizeLogBuffer(buffer, bufferSize, noOfBytesWritten);

    Serial.println(success ? buffer : LOG_ERROR_MSG);
  }
}
