#include"TimeStat.h"
#include<sys/time.h>
#include<stdio.h>

#define __STDC_FORMAT_MACROS
#include<inttypes.h>
#undef __STDC_FORMAT_MACROS


using namespace ety;

TimeStat::TimeStat():m_nMicSecSinceEpoch(0)
{
}

TimeStat::TimeStat(int64_t micSec):m_nMicSecSinceEpoch( micSec )
{
}

string TimeStat::toString() const
{
	char buf[32] = {0};
	int64_t seconds = m_nMicSecSinceEpoch / kMicSecPerSec;
	int64_t micSec = m_nMicSecSinceEpoch % kMicSecPerSec;
	snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, micSec);
	return buf;
}

string TimeStat::toFormatString() const
{
	char buf[32] = {0};
	time_t seconds = static_cast<time_t>(m_nMicSecSinceEpoch / kMicSecPerSec);
	int micSec = static_cast<int>(m_nMicSecSinceEpoch % kMicSecPerSec);
	struct tm tm_time;
	localtime_r(&seconds, &tm_time);
	snprintf(buf, sizeof(buf), "%4d-%2d-%2d %2d:%2d:%2d.%6d", tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, micSec);
	return buf;
}

TimeStat TimeStat::now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t seconds = tv.tv_sec;
	return TimeStat(seconds * kMicSecPerSec + tv.tv_usec);
}
