/*
	TiX Engine v2.0 Copyright (C) 2018
	By ZhaoShuai tirax.cn@gmail.com
*/


#include "stdafx.h"

#include "TTimer.h"
#if defined (TI_PLATFORM_IOS)
#include <sys/time.h>
#elif defined (TI_PLATFORM_WIN32)
#include <time.h>
#pragma comment(lib, "winmm.lib")
#elif defined (TI_PLATFORM_ANDROID)
#include <time.h>
#endif

namespace tix
{
	const long long TTimer::GetCurrentTimeMillis()
	{
#if defined (TI_PLATFORM_WIN32)
		return timeGetTime();
#elif defined (TI_PLATFORM_IOS) || defined (TI_PLATFORM_ANDROID)
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        long long millis = 0;
        //upscale to milliseconds
        millis += currentTime.tv_sec * 1e3;
        //downscale to milliseconds
        millis += currentTime.tv_usec / 1e3;
        return millis;
//#elif defined (TI_PLATFORM_ANDROID)
//		struct timespec now;
//		clock_gettime(CLOCK_MONOTONIC, &now);
//		return (long long) (now.tv_sec*1000000000LL + now.tv_nsec);
#endif
	}

	const int TTimer::GetCurrentTimeSeconds()
	{
		const time_t _time	= time(0);
		struct tm t;
		localtime_s(&t, &_time);

		return	t.tm_hour * 60 * 60 + t.tm_min * 60 + t.tm_sec;
	}

	const int TTimer::GetCurrentTimeSeconds(int& h, int& m, int& s)
	{
		const time_t _time	= time(0);
		struct tm t;
		localtime_s(&t, &_time);

		h		= t.tm_hour;
		m		= t.tm_min;
		s		= t.tm_sec;

		return	t.tm_hour * 60 * 60 + t.tm_min * 60 + t.tm_sec;
	}

	const int TTimer::GetCurrentDate()
	{
		const time_t _time	= time(0);        
		struct tm t;
		localtime_s(&t, &_time);
        
        return t.tm_year * 366 + t.tm_mon * 31 + t.tm_mday;
	}

	const void TTimer::GetYMDFromDate(int date, int& y, int& m, int& d)
	{
		y		= date / 366;
		date	-= y * 366;
		m		= date / 31;
		d		= date - m * 31;
	}

	const int TTimer::GetCurrentDate(int& y, int& m, int& d)
	{
		const time_t _time = time(0);
		struct tm t;
		localtime_s(&t, &_time);

		y	= t.tm_year;
		m	= t.tm_mon;
		d	= t.tm_mday;

		return t.tm_year * 366 + t.tm_mon * 31 + t.tm_mday;
	}

	void	TTimer::GetCurrentWeekDay(int& d)
	{
		const time_t _time = time(0);
		struct tm t;
		localtime_s(&t, &_time);

		d		= t.tm_wday;
	}

	void TTimer::GetCurrentDateAndSeconds(int& d, int& s)
	{
		const time_t _time = time(0);
		struct tm t;
		localtime_s(&t, &_time);

		d		= t.tm_year * 366 + t.tm_mon * 31 + t.tm_mday;
		s       = t.tm_hour * 60 * 60 + t.tm_min * 60 + t.tm_sec;
	}

	bool TTimer::IsLeapYear(int year)
	{
		return (year % 4 == 0 || year % 400 == 0) && (year % 100 != 0);
	}

	int TTimer::DayInYear(int y, int m, int d)
	{
		int DAY[12]	= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (IsLeapYear(y))
			DAY[1]	= 29;

		for (int i = 0 ; i < m - 1 ; ++ i)
		{
			d		+= DAY[i];
		}
		return d;
	}

	int TTimer::DayBetweenDates(int y1, int m1, int d1, int y2, int m2, int d2)
	{
		if (y1 == y2 && m1 == m2)
		{
			return ti_abs(d1 - d2);
		}
		else if (y1 == y2)
		{
			int _d1, _d2;
			_d1		= DayInYear(y1, m1, d1);
			_d2		= DayInYear(y2, m2, d2);
			return ti_abs(_d1 - _d2);
		}
		else
		{
			if (y1 > y2)
			{
				int tmp;
#define TI_SWAP(x, y)	tmp = x; x = y; y = tmp;
				TI_SWAP(y1, y2)
					TI_SWAP(m1, m2)
					TI_SWAP(d1, d2)
#undef TI_SWAP
			}
			int _d1, _d2, _d3;
			// get days left in last year
			if (IsLeapYear(y1))
				_d1		= 366 - DayInYear(y1, m1, d1);	
			else
				_d1		= 365 - DayInYear(y1, m1, d1);

			// get days in current year
			_d2			= DayInYear(y2, m2, d2);

			_d3			= 0;
			for (int y = y1 + 1 ; y < y2 ; ++ y)
			{
				if (IsLeapYear(y))
					_d3	+= 366;
				else
					_d3	+= 365;
			}
			return _d1 + _d2 + _d3;
		}
	}
}
