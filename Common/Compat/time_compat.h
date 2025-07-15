/*
**	Command & Conquer Generals Zero Hour(tm)
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// This file contains the time functions for compatibility with non-windows platforms.
#pragma once

#include <cstdint>
#include <time.h>

struct SYSTEMTIME
{
	uint16_t wYear;
	uint16_t wMonth;
	uint16_t wDayOfWeek;
	uint16_t wDay;
	uint16_t wHour;
	uint16_t wMinute;
	uint16_t wSecond;
	uint16_t wMilliseconds;
};

#define TIMERR_NOERROR 0
typedef int MMRESULT;
static inline MMRESULT timeBeginPeriod(int) { return TIMERR_NOERROR; }
static inline MMRESULT timeEndPeriod(int) { return TIMERR_NOERROR; }

inline unsigned int timeGetTime()
{
  struct timespec ts;
#ifdef __APPLE__
    clock_gettime(CLOCK_UPTIME_RAW, &ts);
#else
  clock_gettime(CLOCK_BOOTTIME, &ts);
#endif
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}
inline unsigned int GetTickCount()
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  // Return ms since boot
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

inline void Sleep(uint32_t ms) {
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, nullptr);
} 

inline void GetLocalTime(SYSTEMTIME *st)
{
  time_t t = time(nullptr);
  struct tm *tm = localtime(&t);
  st->wYear = tm->tm_year + 1900;
  st->wMonth = tm->tm_mon + 1;
  st->wDayOfWeek = tm->tm_wday;
  st->wDay = tm->tm_mday;
  st->wHour = tm->tm_hour;
  st->wMinute = tm->tm_min;
  st->wSecond = tm->tm_sec;
  st->wMilliseconds = 0; // Not supported
}